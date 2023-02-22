IR_Data = (reshape(IR_Image, 1024, []))';
for count = size(IR_Data, 1):-1:1
    Image = IR_Data(count, :);
    Image = (reshape(Image, [], 32))';
    imshow(Image, []);   
    pause(0.5);
end