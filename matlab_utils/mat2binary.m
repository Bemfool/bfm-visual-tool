function mat2binary(filename, mat, type)
    fid=fopen(filename, 'wb');%д���ļ�·��
    matrix = mat;                        %input_matrixΪ���������
    [m,n]=size(matrix);
     for i=1:1:m
       for j=1:1:n
            fwrite(fid, matrix(i,j), type);
       end
    end
    fclose(fid);
end