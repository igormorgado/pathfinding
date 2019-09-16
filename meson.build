project('pathfinding', 'c')

add_project_arguments(['-std=c11', '-Wcast-qual',
	'-Wno-unused-variable', '-Wno-unused-function', '-Wno-unused-parameter'],
	language: 'c')

glibdep = dependency('glib-2.0')
libraries = [ 'gsl' ]
src = ['src/main.c', 'src/io.c']
executable('g', src, dependencies: glibdep)
