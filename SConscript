Import ('env')

name = 'remo'
inc = env.Dir('.')
ext_inc = env.Dir('remo')
src = env.Glob('src/*.cpp') 
deps = ['fideo', 'mili', 'biopp', 'stl-debug', 'biopp-filer']

env.CreateSharedLibrary(name, inc, ext_inc, src, deps)
