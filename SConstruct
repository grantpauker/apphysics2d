OUT = 'a.out'
SOURCE = ['main.cpp', Glob('src/*.cpp')]
LIBS = ['Box2D', 'sfml-graphics', 'sfml-window',
        'sfml-audio', 'sfml-network', 'sfml-system']
CPPPATH = 'src/'
LIBRARY_DIR = '/usr/include/apphysics2d'
HEADERS = Glob("include/apphysics2d/*.hpp")
prog = Program(OUT, SOURCE,
               LIBS=LIBS, CPPPATH=CPPPATH)
install =Install(LIBRARY_DIR, HEADERS)
Alias('install', install)
# env = Environment()
# hello = env.Program('hello.c')
# env.Install('/usr/bin', hello)
# env.Alias('install', '/usr/bin')
