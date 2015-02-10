Import ('env')

name = 'remo'
inc = env.Dir('remo')
deps = ['fideo', 'mili', 'biopp', 'biopp-filer', 'getoptpp', 'acuoso']
src = env.Glob('src/*.cpp')

env.CreateProgram(name, inc, src, deps)