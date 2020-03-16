#version 450

out vec4 FragColor;
in vec2 TexCoords;

layout(location = 0)uniform sampler2D Texture;


//void main()
//{             
//    FragColor = vec4(vec3(1.0 - texture(Texture, TexCoords)), 1.0);
//    //FragColor = texture(Texture, TexCoords);
//}

const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset), // top-left
        vec2(0.0f, offset), // top-center
        vec2(offset, offset), // top-right
        vec2(-offset, 0.0f),   // center-left
        vec2(0.0f, 0.0f),   // center-center
        vec2(offset, 0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f, -offset), // bottom-center
        vec2(offset, -offset)  // bottom-right    
        );

    float kernel[9] = float[](
       1, 0, -1,
        0, 0, 0,
        -1, 0, 1
        );

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(Texture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    float temp = 0.01;
    if (col.r > temp && col.g > temp && col.b > temp)
    {
        col = vec3(0,1,0);
    }
    else
    {
        col = vec3(texture(Texture, TexCoords).rgb);
    }


    FragColor = vec4(col, 1.0);
}