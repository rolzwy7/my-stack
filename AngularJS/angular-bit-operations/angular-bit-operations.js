bit_operations_app = app;

bit_operations_app.factory("BitOperations", function(){
    var factory = {};

    factory.fromInt = function(integer){
        var ret = [];
        if(typeof(integer) === "number") {
            integer = Math.floor(integer);
            while(integer != 0) {
                integer = integer / 2.0;
                w_integer = Math.floor(integer);
                if( (integer - w_integer) == 0 )
                    ret.push("0");
                else
                    ret.push("1");
                integer = w_integer;
            }
        }
        if(ret.length == 0)
            ret = "0";
        else
            ret = ret.reverse().join("");
        return ret;
    };

    factory.toDec = function(binary) {
        var ret =0;
        for(var i=binary.length-1;i>=0;i--) {
            if(binary[i] == "1")
                ret += Math.pow(2, -i+(binary.length-1));
        }
        return ret;
    }

    factory.isSet = function(binary, position) {
        if(position >= 0 && position <= binary.length-1)
            return (binary[-position + (binary.length-1)] == "1") ? true : false;
        else
            return false;
    }

    factory.isPowOfTwo = function(binary) {
        if(binary == "0")
            return false;
        var tmp = 0;
        for(var i=0;i<binary.length;i++) {
            if(binary[i] == "1") {
                tmp = tmp + 1;
            }
            if(tmp > 1)
                return false;
        }
        return true;
    };

    return factory;
});
