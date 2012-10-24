Import ('env')

name = 'remo'
inc = env.Dir('.')
src = env.Glob('src/*.cpp') 
deps = ['fideo', 'mili', 'biopp', 'stl-debug', 'biopp-filer', 'getoptpp']

env.CreateProgram(name, inc, src, deps)
