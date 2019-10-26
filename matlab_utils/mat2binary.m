function mat2binary(filename, mat, type)
    fid=fopen(filename, 'wb');%写入文件路径
    matrix = mat;                        %input_matrix为待输出矩阵
    [m,n]=size(matrix);
     for i=1:1:m
       for j=1:1:n
            fwrite(fid, matrix(i,j), type);
       end
    end
    fclose(fid);
end