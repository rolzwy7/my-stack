var app = angular.module('AppName', []);
app.config(['$interpolateProvider', function($interpolateProvider) {
  $interpolateProvider.startSymbol('{new');
  $interpolateProvider.endSymbol('new}');
}]);