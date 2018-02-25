source_stuff = Environment(LIBS= ['Box2D', 'sfml-graphics', 'sfml-window', 'sfml-audio', 'sfml-network', 'sfml-system'], CPPPATH='src/')

lib_install = source_stuff.Library('apphysics2d', Glob('src/*.cpp'))
lib_create = source_stuff.Install('/usr/lib', 'libapphysics2d.a')

lib_c = Alias('lib-create', lib_install)
lib_i = Alias('lib-install', lib_create)
lib = Alias('library', [lib_c,lib_i])

header_stuff = Environment()
headers = header_stuff.Install('/usr/include/apphysics2d', Glob("include/apphysics2d/*.hpp"))
hed = Alias('headers ',headers)

Alias('install', [lib,hed])

