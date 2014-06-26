function res = sum_alpha(img, alpha)

res = sum(sum(img(:,:,1).*alpha + img(:,:,2).*alpha + img(:,:,3).*alpha));
end