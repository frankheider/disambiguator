
#include <cppunit/Portability.h>
#include <cppunit/portability/CppUnitSet.h>
#include <cppunit/extensions/TestFactory.h>
#include <cppunit/TestCase.h>
#include <string>

// Really good web pages:
// http://stackoverflow.com/questions/318064/how-do-you-declare-an-interface-in-c
// http://stackoverflow.com/questions/7182359/template-instantiation-details-of-gcc-and-ms-compilers
#include <disambiguation.h>
#include <engine.h>
#include <attribute.h>

#include "testdata.h"

using std::string;
using std::cout;
using std::endl;

class AttributeTest : public CppUnit::TestCase {

public:
  AttributeTest(std::string name) : CppUnit::TestCase(name) {}


  void compare_firstname() {

    Record * foobar = make_foobar_record();
    foobar->set_sample_record(foobar);

    cFirstname d1("Dave");
    d1.split_string("Dave");
    cFirstname d2("Dave");
    d2.split_string("Dave");
    d1.activate_comparator();
    //d2.activate_comparator();
    uint32_t similarity = d1.compare(d2);
    //std::cout << "Similarity: " << similarity << std::endl;
    CPPUNIT_ASSERT(4 == similarity);
    similarity = d1.exact_compare(d1);
    //std::cout << "Similarity: " << similarity << std::endl;
  }


  void compare_middlename() {

    Record * foobar = make_foobar_record();
    foobar->set_sample_record(foobar);
    uint32_t similarity;

    cMiddlename d1("David");
    d1.split_string("David");
    cMiddlename d2("David");
    d2.split_string("David");
    cMiddlename d3("David Michael");
    d3.split_string("David Michael");
    cMiddlename d4("David Michael");
    d4.split_string("David Michael");
    cMiddlename d5("Anna Yvette");
    d5.split_string("Anna Yvette");
    cMiddlename d6("AnnaYvette");
    d6.split_string("AnnaYvette");
    cMiddlename d7("Anna");
    d7.split_string("Anna");
    cMiddlename d8("Yvette");
    d8.split_string("Yvette");
    cMiddlename d9("");
    d9.split_string("");
    cMiddlename d10("David Kenneth");
    d10.split_string("David Kenneth");

    d1.activate_comparator();

    similarity = d1.compare(d2);
    std::cout << "Middlename similarity d1, d2: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d1.compare(d3);
    std::cout << "Middlename similarity d1, d3: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d1.compare(d4);
    std::cout << "Middlename similarity d1, d4: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d1.compare(d5);
    std::cout << "Middlename similarity d1, d5: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d1.compare(d6);
    std::cout << "Middlename similarity d1, d6: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d3.compare(d4);
    std::cout << "Middlename similarity d3, d4: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d8.compare(d9);
    std::cout << "Middlename similarity d8, d9: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

    similarity = d4.compare(d10);
    std::cout << "Middlename similarity d4, d10: " << similarity << std::endl;
    //CPPUNIT_ASSERT(4 == similarity);

  }


  // Test for memory leakage using valgrind
  void delete_attribute() {
    cFirstname * a = new cFirstname("Dave");
    delete a;
  }

  void runTest() {
    compare_firstname();
    compare_middlename();
    delete_attribute();
  }
};


int
main(int UP(argc), char ** UP(argv)) {

  AttributeTest * at = new AttributeTest(std::string("initial test"));
  at->runTest();
  delete at;
  return 0;
}
