function validateConfiguration() {
  var orig = $('input[name=orig-type]:checked').val();
  var tar = $('input[name=tar-type]:checked').val();
  var variant = $('input[name=variant-type]:checked').val();
  var idiom = $('input[name=idiom-type]:checked').val();

  if (orig === 'simp') {
    if (tar === 'simp') {
      //簡體到簡體
      return true;
    } else if (tar === 'trad') {
      //簡體到繁體
      if (variant === 'opencc') {
        //OpenCC異體字
        if (idiom === 'disabled') {
          //不轉換詞彙
          return 's2t';
        } else if (idiom === 'mainland') {
          //大陸詞彙(TODO)
        } else if (idiom === 'taiwan') {
          //臺灣詞彙(TODO)
        }
      } else if (variant === 'taiwan') {
        //臺灣異體字
        if (idiom === 'disabled') {
          //不轉換詞彙
          return 's2tw';
        } else if (idiom === 'mainland') {
          //大陸詞彙(TODO)
        } else if (idiom === 'taiwan') {
          //臺灣詞彙
          return 's2twp';
        }
      } else if (variant === 'hongkong') {
        // 香港異體字
        if (idiom === 'disabled') {
          //不轉換詞彙
          return 's2hk';
        } else if (idiom === 'mainland') {
          //大陸詞彙(TODO)
        } else if (idiom === 'taiwan') {
          //臺灣詞彙(TODO)
        }
      }
    }
  } else if (orig === 'trad') {
    if (tar === 'simp') {
      //繁體到簡體
      if (idiom === 'disabled') {
        //不轉換詞彙
        return 't2s';
      } else if (idiom === 'mainland') {
        //大陸詞彙
        return 'tw2sp';
      } else if (idiom === 'taiwan') {
        //臺灣詞彙（TODO）
      }
    } else if (tar === 'trad') {
      //繁體到繁體
      if (variant === 'opencc') {
        //OpenCC異體字
        if (idiom === 'disabled') {
          //不轉換詞彙
          return true;
        } else if (idiom === 'mainland') {
          //大陸詞彙
        } else if (idiom === 'taiwan') {
          //臺灣詞彙
        }
      } else if (variant === 'taiwan') {
        //臺灣異體字
        if (idiom === 'disabled') {
          //不轉換詞彙
        } else if (idiom === 'mainland') {
          //大陸詞彙(TODO)
        } else if (idiom === 'taiwan') {
          //臺灣詞彙
        }
      }
    }
  }
  return undefined;
}

function sendRequests(arg, callback) {
  var config = arg['config'];
  var text = $('#text').val();
  callback(undefined, opencc_convert(config,text))
}

function doConvert(event) {
  var precise = event.data && event.data['precise'];

  $('#convert').button('disable');
  $('#precise-convert').button('disable');
  $('#text').attr('readonly', 'readonly');
  $('#text').fadeTo('fast', 0.5);

  var config = validateConfiguration();
  if (!config) {
    $('#dialog-config-error').dialog({
      height: 140,
      modal: true
    });
    resetProgress();
    return;
  }

  if (config === true) {
    resetProgress();
    return;
  }

  sendRequests({
    config: config,
    precise: precise,
  }, function (err, text) {
    if (err) {
      if (err == 'error') {
        err = '請求發送失敗。';
      }
      $('#dialog-request-error p').html(err);
      $('#dialog-request-error').dialog({
        height: 140,
        modal: true,
      });
      return;
    }

    $('#text').val(text);
    resetProgress();
  });
}

function resetProgress() {
  $('#text').fadeTo('fast', 1);
  $('#text').removeAttr('readonly');
  $('#convert').button('enable');
  $('#precise-convert').button('enable');
  $('#convert').show();
  $('#precise-convert').show();
  $('#new-convert').hide();
  $('#proof').hide();
}

$(function () {
  $('#main-tabs').tabs();
  $('#orig-type').buttonset();
  $('#tar-type').buttonset();
  $('#variant-type').buttonset();
  $('#idiom-type').buttonset();
  $('#convert').button();
  $('#precise-convert').button();
  $('#new-convert').button();

  $('#tar-type-simp').click(function () {
    $('#variant-type').hide('fast');
  });
  $('#tar-type-trad').click(function () {
    $('#variant-type').show('fast');
  });

  $('#text').width('100%');
  $('#convert').click({
    precise: 0,
  }, doConvert);
  $('#precise-convert').click({
    precise: 1,
  }, doConvert);
  $('#new-convert').click(resetProgress).hide();
});
