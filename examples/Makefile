# Makefile -- Sample build instructions for example.
#
# Copyright 2022 Stéphane Caron
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# I configured my CMAKE_INSTALL_PREFIX to ~/.local using ccmake. If you did
# not, the default was /usr/local. Uncomment the line below accordingly.
MY_CMAKE_INSTALL_PREFIX=${HOME}/.local
# MY_CMAKE_INSTALL_PREFIX=/usr/local

CPP=g++
IFLAGS=-I$(MY_CMAKE_INSTALL_PREFIX)/include $(shell pkg-config eigen3 --cflags)
LFLAGS=-L$(MY_CMAKE_INSTALL_PREFIX)/lib -lmpack -lpalimpsest

.PHONY: all clean cpp_to_python help readme

%.out: %.cpp
	@$(CPP) $(IFLAGS) $< $(LFLAGS) -o $@

# Help snippet from https://github.com/fzaninotto/Faker/blob/master/Makefile
help:  ## print this help
	@grep -P '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
.DEFAULT_GOAL := help

all: readme cpp_to_python  ## run all examples
	@echo ""

readme: readme.out  ## README example
	@echo ""
	@echo "README example"
	@echo "=============="
	@./readme.out

cpp_to_python: cpp_to_python.out  ## send a Dictionary from C++ to Python
	@echo ""
	@echo "cpp_to_python: C++ writer"
	@echo "========================="
	@./cpp_to_python.out
	@echo ""
	@echo "cpp_to_python: Python reader"
	@echo "============================"
	@python cpp_to_python.py

clean:  ## clean compiled binaries
	rm -f $(wildcard *.out)
