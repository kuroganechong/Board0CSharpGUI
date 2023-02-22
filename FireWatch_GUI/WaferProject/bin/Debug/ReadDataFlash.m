clear all
clc
close all

fileID = fopen('Flashlog132484166413807847.txt','r');
C = textscan(fileID,'%s');
fclose(fileID);
C1 = C{1,1};
n = size(C1,1);
idx = 1;
IR_Image = [];
Frame_Number = [];
while idx <= n
    temp = C1{idx,1};
    if numel(temp)>1
        temp1 = temp(1:2);
    else
        temp1 = temp;
    end
    switch(temp1)
        case 'ti'
            idx = idx + 3;
            CellTemp = C1(idx: idx + 3071);
            IR_Image = vertcat(IR_Image, str2double(CellTemp));
            idx = idx + 3071;
         case 'Ra'
            idx = idx + 2;
            CellTemp = C1(idx: idx + 2);
            CellTemp = str2double(CellTemp); 
            Frame_Number = vertcat(Frame_Number, CellTemp);
            idx = idx + 2;
        otherwise
    end
    idx = idx + 1;
end