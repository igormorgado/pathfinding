# vim:ts=4:sw=4:et:tw=0:ft=python
project('pathfinding', 'c')
add_project_arguments(['-std=c11',
                       '-Wcast-qual',
                       '-Wno-unused-variable',
                       '-Wno-unused-function',
                       '-Wno-unused-parameter'],
                      language: 'c')

bin = 'main'

deps = [dependency('glib-2.0'),
        dependency('gsl')]

src = ['src/main.c',
       'src/graph.c',
       'src/io.c',
       'src/matrix.c']
    
executable(bin, sources: src, dependencies: deps)


