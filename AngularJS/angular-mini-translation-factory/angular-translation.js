// Config - start
translation_factory = app;
translation_parent_dir = "./assets"
// Config - end

_tpd = translation_parent_dir + "/translation/"
_flags_images_dirpath   = _tpd + "flags";
_config_path            = _tpd + "config.json";
_translations_path            = _tpd + "translations.json";

_flags_ext = "png"

translation_factory.factory("Translation", function($http, $q) {
    var factory = {};

    factory.getConfig = function() {
        return $q(function(resolve, reject){
            $http({
            method: 'GET',
            url: _config_path
            }).then(function success(response) {
                resolve(response);
            }, function error(response) {
                reject(response);
            });
        });
    };

    factory.getFlag = function(flagname) {
        return _flags_images_dirpath + "/" + flagname + "." + _flags_ext;
    };

    factory.getTranslations = function(code) {
        return $q(function(resolve, reject){
            $http({
            method: 'GET',
            url: _translations_path
            }).then(function success(response) {
                resolve(response);
            }, function error(response) {
                reject(response);
            });
        });
    };

    return factory;
});
