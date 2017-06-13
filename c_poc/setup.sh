#!/bin/bash

pushd includes
	tar -vxf openssl_headers.tar.gz
popd

make
make oclean
