#include <emscripten/bind.h>
#include "../src/Config.hpp"
#include "../src/Converter.hpp"
#include "../src/Exception.hpp"
#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <map>

using namespace emscripten;

std::map<std::string,std::string> configJson = // new std::map<std::string,std::string>();
{ {"hk2s", "{  \"name\": \"Traditional Chinese (Hong Kong standard) to Simplified Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TSPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"HKVariantsRevPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"HKVariantsRev.ocd\"      }]     }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TSPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TSCharacters.ocd\"      }]    }  }]}"},
  {"s2hk", "{  \"name\": \"Simplified Chinese to Traditional Chinese (Hong Kong standard)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"STPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"STPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"STCharacters.ocd\"      }]    }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"HKVariantsPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"HKVariants.ocd\"      }]     }  }]}"},
  {"s2t", "{  \"name\": \"Simplified Chinese to Traditional Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"STPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"STPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"STCharacters.ocd\"      }]    }  }]}"},
  {"s2tw", "{  \"name\": \"Simplified Chinese to Traditional Chinese (Taiwan standard)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"STPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"STPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"STCharacters.ocd\"      }]    }  }, {    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWVariants.ocd\"    }  }]}"},
  {"s2twp", "{  \"name\": \"Simplified Chinese to Traditional Chinese (Taiwan standard, with phrases)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"STPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"STPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"STCharacters.ocd\"      }]    }  }, {    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWPhrases.ocd\"    }  }, {    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWVariants.ocd\"    }  }]}"},
  {"t2hk", "{  \"name\": \"Traditional Chinese to Traditional Chinese (Hong Kong standard)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"HKVariants.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"ocd\",      \"file\": \"HKVariants.ocd\"    }  }]}"},
  {"t2s", "{  \"name\": \"Traditional Chinese to Simplified Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TSPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TSPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TSCharacters.ocd\"      }]    }  }]}"},
  {"t2tw", "{  \"name\": \"Traditional Chinese to Traditional Chinese (Taiwan standard)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWVariants.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWVariants.ocd\"    }  }]}"},
  {"tw2s", "{  \"name\": \"Traditional Chinese (Taiwan standard) to Simplified Chinese\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TSPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TWVariantsRevPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TWVariantsRev.ocd\"      }]     }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TSPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TSCharacters.ocd\"      }]    }  }]}"},
  {"tw2sp", "{  \"name\": \"Traditional Chinese (Taiwan standard) to Simplified Chinese (with phrases)\",  \"segmentation\": {    \"type\": \"mmseg\",    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TSPhrases.ocd\"    }  },  \"conversion_chain\": [{    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TWVariantsRevPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TWVariantsRev.ocd\"      }]     }  }, {    \"dict\": {      \"type\": \"ocd\",      \"file\": \"TWPhrasesRev.ocd\"    }  }, {    \"dict\": {      \"type\": \"group\",      \"dicts\": [{        \"type\": \"ocd\",        \"file\": \"TSPhrases.ocd\"      }, {        \"type\": \"ocd\",        \"file\": \"TSCharacters.ocd\"      }]    }  }]}"}
};

std::map<std::string, opencc::ConverterPtr> converters = {};
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> ws_converter;

std::wstring convert(std::string configType, std::string inputString){
    if (configJson.find(configType) == configJson.end()) {
        throw "Error: config not found\n";
    }
    opencc::Config config;
    opencc::ConverterPtr cvt;
    try {
        // check if a converter exists
        if (converters.find(configType) == converters.end()) {
            auto json = configJson[configType];       
            converters[configType] = config.NewFromString(*(new std::string(json)), "data/");
        }
        cvt = converters[configType];
    } catch (const std::exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (const opencc::Exception& e) {
        std::cout<<e.what()<<std::endl;
    } catch (...) {
        std::cout<<"Unknown exception\n";
    }

    std::string result = cvt->Convert(inputString);
    
    std::wstring wide = ws_converter.from_bytes(result);
    return wide;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("convert", &convert);
}