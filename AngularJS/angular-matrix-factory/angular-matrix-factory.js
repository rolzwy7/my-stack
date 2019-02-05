var matrix_app = app;

matrix_app.factory("Matrix", function() {
    var factory = {};
    // copy matrix contents
    factory.copyMatrix = function(matrix) {
        var ret = this.filled(matrix.length, matrix[0].length, 0);
        for(var i=0;i<matrix.length;i++)
            for(var j=0;j<matrix[i].length;j++)
                ret[i][j] = matrix[i][j];
        return ret;
    };
    // Create filled matrix
    factory.filled = function(rows_num, cols_num, fill) {
        var ret = [];
        for(var i=0;i<rows_num;i++) {
            var tmp = [];
            for(var j=0;j<cols_num;j++)
                tmp.push(fill);
            ret.push(tmp);
        }
        return ret;
    };
    // Create eye matrix
    factory.eye = function(num) {
        var ret = this.filled(num, num, 0);
        for(var i=0;i<num;i++)
            ret[i][i] = 1;
        return ret;
    };
    // sum matrix elements
    factory.sum = function(matrix) {
        var ret = 0;
        for(var i=0;i<matrix.length;i++)
            for(var j=0;j<matrix[i].length;j++)
                ret += matrix[i][j];
        return ret;
    };
    // min of matrix
    factory.min = function(matrix) {
        var ret = matrix[0][0];
        for(var i=0;i<matrix.length;i++)
            for(var j=0;j<matrix[i].length;j++)
                if(ret > matrix[i][j]) ret = matrix[i][j];
        return ret;
    };
    // max of matrix
    factory.max = function(matrix) {
        var ret = matrix[0][0];
        for(var i=0;i<matrix.length;i++)
            for(var j=0;j<matrix[i].length;j++)
                if(ret < matrix[i][j]) ret = matrix[i][j];
        return ret;
    };
    // Fill column
    factory.fillColumn = function(matrix, col_num, fill) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(j === col_num)
                    ret[i][j] = fill;
        return ret
    };
    // Fill row
    factory.fillRow = function(matrix, rows_num, fill) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(i === rows_num)
                    ret[i][j] = fill;
        return ret
    };
    // Zero column
    factory.zeroColumn = function(matrix, col_num) {
        return this.fillColumn(matrix, col_num, 0);
    };
    // Zero row
    factory.zeroRow = function(matrix, rows_num) {
        return this.fillRow(matrix, rows_num, 0);
    };
    // cross replace on element found
    factory.crossReplace = function(matrix, target, replace) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(ret[i][j] === target) {
                    ret = this.fillColumn(ret, j, replace);
                    ret = this.fillRow(ret, i, replace);
                }
        return ret;
    };
    // cross replace on element found
    factory.crossReduction = function(matrix, row, col) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(i === row && j === col) {
                    ret = this.fillColumn(ret, j, "del");
                    ret = this.fillRow(ret, i, "del");
                }
        var ret_reduced = [];
        var tmp = [];
        for(var i=0;i<ret.length;i++) {
            tmp = []
            for(var j=0;j<ret[i].length;j++) {
                if(ret[i][j] != "del")
                    tmp.push(ret[i][j]);
            }
            if(tmp.length != 0)
                ret_reduced.push(tmp);
        }
        return ret_reduced;
    };
    // horizontal replace on element found
    factory.horizontalReplace = function(matrix, target, replace) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(ret[i][j] === target) {
                    ret = this.fillRow(ret, i, replace);
                }
        return ret;
    };
    // vertical replace on element found
    factory.verticalReplace = function(matrix, target, replace) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++)
                if(ret[i][j] === target) {
                    ret = this.fillColumn(ret, j, replace);
                }
        return ret;
    };
    // apply function on elements
    // first argument of func need to be reserved for matrix element
    // func must return
    factory.functionApply = function(matrix, func, args=[]) {
        var ret = this.copyMatrix(matrix);
        for(var i=0;i<ret.length;i++)
            for(var j=0;j<ret[i].length;j++) {
                var tmp_func;
                if(args.length != 0)
                    tmp_func = "func(ret[i][j], " + args.join(",") + ")";
                else
                    tmp_func = "func(ret[i][j])";
                ret[i][j] = eval(tmp_func);
            }
        return ret;
    };
    // Transposition
    factory.T = function(matrix) {
        var ret = this.copyMatrix(matrix);
        var ret_t = []
        var tmp;
        for(var j=0;j<ret[0].length;j++) {
            tmp = [];
            for(var i=0;i<ret.length;i++) {
                tmp.push(ret[i][j]);
            }
            ret_t.push(tmp);
        }
        console.log(ret_t);
        return ret_t;
    };

    // det of 2x2 matrix
    factory.det2by2 = function(matrix) {
        var ret = this.copyMatrix(matrix);
        if(ret.length == 2 && ret[0].length == 2)
            return (ret[0][0] * ret[1][1]) - (ret[0][1] * ret[1][0]);
        return false;
    }

    // switch two rows
    factory.switchRows = function(matrix, row_1, row_2) {
        var ret = this.copyMatrix(matrix);
        if(ret.length < 2) {return false;}
        if( (0 <= row_1 && row_1 <= ret.length-1) && (0 <= row_2 && row_2 <= ret.length-1) ) {
            var tmp_row = ret[row_1];
            ret[row_1] = ret[row_2];
            ret[row_2] = tmp_row;
            return ret;
        } else {
            return false;
        }
    }

    // switch two cols
    factory.switchCols = function(matrix, col_1, col_2) {
        var ret = this.copyMatrix(matrix);
        if(ret[0].length < 2) {return false;}
        if( (0 <= col_1 && col_1 <= ret[0].length-1) && (0 <= col_2 && col_2 <= ret[0].length-1) ) {

            for(var i=0;i<ret.length;i++) {
                var tmp_col = ret[i][col_1];
                ret[i][col_1] = ret[i][col_2];
                ret[i][col_2] = tmp_col;
            }
            return ret;
        } else {
            return false;
        }
    }

    // calc det
    factory.det = function(matrix) {
        var ret = this.copyMatrix(matrix);
        var ret_array = [];
        var tmp_reduced_matrix;
        if(ret.length != ret[0].length) {
            console.log("rows != cols");
            return false;
        }
        for(var j=0;j<ret[0].length;j++) {
            var current_number = ret[0][j];
            tmp_reduced_matrix = this.crossReduction(ret, 0, j);

            if(tmp_reduced_matrix.length == 2 && tmp_reduced_matrix[0].length ==2) {
                if( (1+(j+1)) % 2 == 1 )
                    tmp_reduced_matrix = this.switchRows(tmp_reduced_matrix, 1, 0);
                ret_array.push( current_number * this.det2by2(tmp_reduced_matrix) );
            } else {
                if( (1+(j+1)) % 2 == 1 )
                    ret_array = ret_array.concat( -current_number * this.det(tmp_reduced_matrix) );
                else
                    ret_array = ret_array.concat( current_number * this.det(tmp_reduced_matrix) );
            }

        }
        console.log(ret_array);
        return ret_array.reduce((a, b) => a + b, 0);
    };

    return factory;
});
