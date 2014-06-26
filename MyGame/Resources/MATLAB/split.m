function split(img,alpha, index)

if (sum_alpha(img,alpha) <= 20)
    %imwrite(img, strcat('player/',strcat(int2str(index), '_dummy.png')),'alpha', alpha);
    clear img;
    clear alpha;
    return;
end

[w,h,t] = size(img);
for x = 5 : w - 5
    if (sum_alpha(img(x,:,:),alpha(x,:,:)) <= 20)
        % split imgs
        index = index + 1;
        split(img(1:x-1, :,:),alpha(1:x-1,:,:), index);
        index = index + 1;
        split(img(x:end,:,:),alpha(x:end,:,:), index);
        return;
    end
end

for y = 5 : h - 5
    if (sum_alpha(img(:,y,:),alpha(:,y,:)) <= 20)
        index = index + 1;
        split(img(:, 1:y-1,:),alpha(:,1:y-1,:), index);
        index = index + 1;
        split(img(:,y:end,:),alpha(:,y:end,:), index);
        return;
    end
end

imwrite(img, strcat('',strcat(int2str(index), '.png')),'alpha', alpha);
    clear img;
    clear alpha;
end