function res = sum_alpha2(img, alpha)

res = img;
res(:,:,1) = img(:,:,1).*alpha;
res(:,:,2) = img(:,:,2).*alpha;
res(:,:,3) = img(:,:,3).*alpha;
end