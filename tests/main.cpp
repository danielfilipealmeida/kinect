#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch_amalgamated.hpp"
#include "SetLoader.hpp"


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}


TEST_CASE("Can read filters from set file", "[SetLoader]") {
    SetLoader setLoader;
    
    ofJson expectedFilters = {"invertcolor", "limiter"};
    
    setLoader.filtersLambda = [expectedFilters](ofJson data) {
        REQUIRE(data.dump() == expectedFilters.dump());
    };
    setLoader.loadFile( std::string(ofFilePath::getCurrentWorkingDirectory()) + "/data/set1.json");
}


TEST_CASE("Can read input from set file", "[SetLoader]") {
    SetLoader setLoader;
    
    ofJson expectedInputs = {{{"type", "video"}, {"path", "Glitch001.mov"}}, {{"type", "video"}, {"path", "Glitch002.mov"}}};
    
    setLoader.inputsLambda = [expectedInputs](ofJson data) {
        REQUIRE(data.dump() == expectedInputs.dump());
    };
    setLoader.loadFile( std::string(ofFilePath::getCurrentWorkingDirectory()) + "/data/set1.json");
}
