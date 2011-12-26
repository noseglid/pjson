## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = foreign 1.7

ACLOCAL_AMFLAGS = -I m4

# Libtools versioning is as follows: current:revision:age (c:r:a)
#
#  * If anything have changed in the source code, increase revision.
#    Next version will be (c:r+1:a)
#
#  * If interface have changed (added, removed or changed functions)
#    Next version will be (c+1:0:a)
#
#  * If any interfaces have been added, increate age.
#    Next version will be (c:r:a+1)
#
#  * If any interfaces have been removed or changed, reset age to 0.
#    Next versiom will be (c:r:0)
#
VERSION_INFO = 1:0:0

# Release versioning is (major:minor)
# The Name of the final version will me (major:minor:interface)
# where interface is described by the VERSION_INFO above.
RELEASE = 0.2

GENERIC_LDFLAGS = -release $(RELEASE) -version-info $(VERSION_INFO)

lib_LTLIBRARIES = libpjson.la

libpjson_la_SOURCES = pjson/JsonValue.cpp
libpjson_la_LDFLAGS = $(GENERIC_LDFLAGS)

include_HEADERS        = pjson/pjson.hpp
nobase_include_HEADERS = pjson/JsonBuilder.hpp \
                         pjson/JsonException.hpp \
                         pjson/JsonValue.hpp

# Create a target for easy testing.
# The makefile in the tests folder is not in anyway
# platform independant so it does not need to be advertised
# that it exists.
test:
	$(MAKE) -C tests test
