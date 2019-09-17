# vim:ts=4:sw=4:et:tw=0:ft=python
project('pathfinding', 'c')

add_project_arguments(['-std=c11',
                       '-Wcast-qual',
                       '-Wno-unused-variable',
                       '-Wno-unused-function',
                       '-Wno-unused-parameter'],
                      language: 'c')

bin = 'main'
bfs = 'bfs'

deps = [dependency('glib-2.0'),
        dependency('gsl')]

mainsrc = ['src/main.c',
           'src/graph.c',
           'src/io.c',
           'src/matrix.c']

bfssrc = ['src/bfs.c',
          'src/graph.c']
    
executable(bin, sources: mainsrc, dependencies: deps)
executable(bfs, sources: bfssrc, dependencies: deps)


