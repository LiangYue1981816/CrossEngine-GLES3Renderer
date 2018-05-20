glslc -I".\inc" SkyBox.vert -o SkyBox.vert.bin
glslc -I".\inc" SkyBox.frag -o SkyBox.frag.bin

glslc -I".\inc" BRDF_Pbr.vert -o BRDF_Pbr.vert.bin
glslc -I".\inc" BRDF_Pbr.frag -o BRDF_Pbr.frag.bin

glslc -I".\inc" BRDF_PbrIBL.vert -o BRDF_PbrIBL.vert.bin
glslc -I".\inc" BRDF_PbrIBL.frag -o BRDF_PbrIBL.frag.bin

glslc -I".\inc" BRDF_Blinn.vert -o BRDF_Blinn.vert.bin
glslc -I".\inc" BRDF_Blinn.frag -o BRDF_Blinn.frag.bin

pause