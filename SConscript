Import ('env')

name = 'remo'
inc = env.Dir('remo')
deps = ['fideo', 'mili', 'biopp', 'stl-debug', 'biopp-filer', 'getoptpp']

src = env.Glob('src/*.cpp') 
src.remove(env.File('src/Main.cpp'))
env.CreateObject('remo-objects', inc, src, deps)

deps += ['remo-objects']
env.CreateProgram(name, inc, ['src/Main.cpp'], deps)
