# compiler
cc := g++

# source code
cli_src := main.cc src/text-client.cc src/shared-file-manager.cc
srv_src := main.cc src/text-server.cc src/shared-file-manager.cc
src := main.cc src/text-server.cc src/text-server.cc src/text-client.cc src/shared-file-manager.cc

# final executables
cli_exe := text-client
srv_exe := text-server

# compile flags
flags := -std=c++17 
linker_libs = -L/lib -lpthread -lrt

# compile command
compile.cc = $(cc) $(flags) $^ -o $@ #$(linker_libs)

# make
$(cli_exe): $(src)
	$(compile.cc)

$(srv_exe): $(src)
	$(compile.cc)

clean:
	rm -r $(cli_exe) $(srv_exe)
