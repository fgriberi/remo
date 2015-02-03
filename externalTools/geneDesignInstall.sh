#!/bin/bash

#Step 1: check ubuntu dependencies
echo -e "\e[1;32mChecking ubuntu dependencies\e[0m"
function checkInstalled
{
    if !(which $1 > /dev/null); then
        echo -e "\e[1;31m$1 is not installed. This script is for an ubuntu-based distribution.\e[0m"
        echo -e "\e[1;31mYou will need to install the dependencies manually.\e[0m"        
        exit 1
    fi
}

checkInstalled dpkg
checkInstalled apt-cache
checkInstalled apt-get

#Step 2: check git dependence
echo -e "\e[1;32mChecking git dependence\e[0m"
if !(dpkg -l | grep git -c >>/dev/null); then 
    echo -e "\e[1;32mGit not installed. Installing it...\e[0m"
    sudo apt-get install git
fi

#Step 3: check apache2 dependence
echo -e "\e[1;32mChecking apache2 dependence\\e[0m"
if !(dpkg -l | grep apache2 -c >>/dev/null); then 
    echo -e "\e[1;32mApache2 not installed. Installing it...\e[0m"
    sudo apt-get install apache2
fi

#Step 4: download geneDesing project
echo -e "\e[1;32mDownloading geneDesign\e[0m"
git clone https://github.com/GeneDesign/GeneDesign.git

#Step 5: install cpan dependencies
echo -e "\e[1;32mInstalling CPAN dependencies\e[0m"
sudo perl -MCPAN -e 'install CGI'
sudo perl -MCPAN -e 'install GD::Graph'
sudo perl -MCPAN -e 'install Text::Wrap'
sudo perl -MCPAN -e 'install Perl6::Slurp'
sudo perl -MCPAN -e 'install List::Util'
sudo perl -MCPAN -e 'install List::MoreUtils'

#Step 6: install geneDesign dependencies
echo -e "\e[1;32mInstalling geneDesign dependencies\e[0m"
cd GeneDesign
sudo perl genedesign_mod_install.pl

#Step 7: apply geneDesign fix
echo -e "\e[1;32mApplying the fix for geneDesign\e[0m"
sed -i -e 's/IO::Socket::INET->new( PeerAddr=> "baderlab.bme.jhu.edu", PeerPort=> 80, Proto   => "tcp")/"127.0.0.1"/g' bin/GeneDesign.pm
sed -i -e 's/$sock->sockhost/$sock/g' bin/GeneDesign.pm

#Step 8: configure apache server
echo -e "\e[1;32mConfigurating local server\e[0m"
sudo rm /etc/apache2/sites-available/default
APACHE_CONF="<VirtualHost *:80>
    ServerAdmin webmaster@localhost

    DocumentRoot /var/www
    <Directory />
        Options FollowSymLinks
        AllowOverride None
    </Directory>
    <Directory /var/www/>
        Options Indexes FollowSymLinks MultiViews
        AllowOverride None
        Order allow,deny
        allow from all
    </Directory>

    <Directory $(pwd)/documents/gd> 
        Options Indexes MultiViews FollowSymLinks
        AllowOverride All
        Order allow,deny
        Allow from all
    </Directory>

    <Directory $(pwd)/cgi-bin/gd>  
        AllowOverride None
        Options ExecCGI
        Order allow,deny
        Allow from all
    </Directory>

    ScriptAlias /cgi-bin/gd/ $(pwd)/cgi-bin/gd
    ScriptAlias /cgi-bin/ /usr/lib/cgi-bin/
    <Directory /usr/lib/cgi-bin>
        AllowOverride None
        Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
        Order allow,deny
        Allow from all
    </Directory>

    ErrorLog ${APACHE_LOG_DIR}/error.log

    # Possible values include: debug, info, notice, warn, error, crit,
    # alert, emerg.
    LogLevel warn

    CustomLog ${APACHE_LOG_DIR}/access.log combined

    Alias /gd $(pwd)/documents/gd
    Alias /doc/ /usr/share/doc/
    <Directory /usr/share/doc/>
        Options Indexes MultiViews FollowSymLinks
        AllowOverride None
        Order deny,allow
        Deny from all
        Allow from 127.0.0.0/255.0.0.0 ::1/128
    </Directory>
</VirtualHost>"

#sudo echo "${APACHE_CONF}" >> /etc/apache2/sites-available/default
echo "${APACHE_CONF}" | sudo tee /etc/apache2/sites-available/default

#Step 9: restart server
echo -e "\e[1;32mRestarting local server\e[0m"
sudo /etc/init.d/apache2 restart

# Step 10: run geneDesing test
echo -e "\e[1;32mRuning geneDesing test\e[0m"
cd bin
perl Reverse_Translate.pl -i Test_YAR000W_p.FASTA -o 13

#Step 11: Check instalation status
OUTPUT_DIRECTORY="Test_YAR000W_p_gdRT"
OUTPUT_FILE_1=$OUTPUT_DIRECTORY"/Test_YAR000W_p_gdRT_1.FASTA"
OUTPUT_FILE_2=$OUTPUT_DIRECTORY"/Test_YAR000W_p_gdRT_3.FASTA"

if [ -f $OUTPUT_FILE_1 ];
then
   echo -e "\e[1;32mGeneDesign installed successfully!!!\e[0m"      
   rm -rf $OUTPUT_DIRECTORY
else
   echo -e "\e[1;31mGeneDesign not installed. Please check step by step manually!!!\e[0m"
fi
