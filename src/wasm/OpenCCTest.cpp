
#include "../Config.hpp"
#include "../Converter.hpp"
#include "../Exception.hpp"
#include <string>
#include <iostream>
const std::string hk2s="{  \"name\": \"Traditional Chinese (Hong Kong standard) to Simplified Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"text\",      \"file\": \"TSPhrases.txt\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"text\",        \"file\": \"HKVariantsRevPhrases.txt\"      }, {        \"type\": \"text\",        \"file\": \"HKVariantsRev.txt\"      }]     }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"text\",        \"file\": \"TSPhrases.txt\"      }, {        \"type\": \"text\",        \"file\": \"TSCharacters.txt\"      }]    }  }]}";
const std::string hk2s_ocd="{  \"name\": \"Traditional Chinese (Hong Kong standard) to Simplified Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TSPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"HKVariantsRevPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"HKVariantsRev.ocd\"      }]     }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TSPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TSCharacters.ocd\"      }]    }  }]}";

int main() {
    std::cout << hk2s <<std::endl;
    //std::cout<<"size_t is "<<sizeof(size_t)<<std::endl;
    //std::cout<<"int64_t is "<<sizeof(int64_t)<<std::endl;
    //std::cout<<"int32_t is "<<sizeof(int32_t)<<std::endl;
    opencc::Config config;
    std::string inputString = "香港繁體字來自羅馬简体字呢?";
    //std::string inputString = "體";
    opencc::ConverterPtr cvt;
    try {
       cvt = config.NewFromString(hk2s_ocd, "data/");

    } catch (const std::exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (const opencc::Exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (...) {
        std::cout<<"Unknown exception\n";
    }

    std::cout<<"config loaded"<<std::endl;

    try {
         std::cout<<inputString<< cvt->Convert(inputString) <<std::endl;

    } catch (const std::exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (const opencc::Exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (...) {
        std::cout<<"Unknown exception\n";
    }


    return 0;

}

std::string getconfig() {
    return hk2s;
}