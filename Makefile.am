## ProcessExecutor

AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}

lib_LTLIBRARIES = libprocessexecutor.la

AM_CXXFLAGS = -O0 -lpthread -std=c++0x -I$(libdir)

libprocessexecutor_la_SOURCES = src/safestream.h src/process.h src/process.cpp 	\
				src/safeinputstream.cpp src/safeoutputstream.h 					\
				src/safeoutputstream.cpp src/safestream.cpp src/safeinputstream.h
				
library_includedir=$(includedir)/processexecutor
library_include_HEADERS = src/process.h src/safeinputstream.h \
				src/safeoutputstream.h src/safestream.h
