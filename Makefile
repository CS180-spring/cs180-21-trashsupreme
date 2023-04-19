GTEST_DIR=Database/Tests/googletest/googletest

test:
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
    -pthread -c ${GTEST_DIR}/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

	g++ -isystem ${GTEST_DIR}/include -pthread Database/Tests/unitTest.cpp libgtest.a -o DatabaseUnitTester
