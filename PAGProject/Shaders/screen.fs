#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform bool doToonShading;
uniform bool doPixelationShading;
uniform float toneExposure;
uniform float gamma;

const float offset = 1.0 / 300.0;  


float toonify(in float intensity) {
    if (intensity > 0.8)
        return 1.0;
    else if (intensity > 0.5)
        return 0.8;
    else if (intensity > 0.25)
        return 0.3;
    else
        return 0.1;
}

vec3 toneMapping(vec3 color)
{
    color *=toneExposure/(1. + color / toneExposure);
    color = pow(color, vec3(1. / 2.2));
    return color;
}

vec3 gammaCorrection(vec3 color)
{
    color = pow(color.rgb, vec3(1/gamma));
    return color;
}

void main()
{ 
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        -1./9, -1./9, -1./9,
        -1./9, 1., -1./9,
        -1./9, -1./9, -1./9
    );
    
    float sx[9] = float[]( 
        1.0, 2.0, 1.0, 
        0.0, 0.0, 0.0, 
        -1.0, -2.0, -1.0 
    );
    float sy[9] = float[]( 
        1.0, 0.0, -1.0, 
        2.0, 0.0, -2.0, 
        1.0, 0.0, -1.0 
    );
    
    if(doToonShading)
    {
        vec3 sampleTex[9];
        float I[9];
        for(int i =0; i <9; ++i)
        {
            sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
            I[i] = length(sampleTex[i]);
        }
        vec3 colx = vec3(0.0);
        vec3 coly = vec3(0.0);
        for(int i =0; i<9; ++i)
        {
            colx += I[i] *sx[i];
            coly += I[i] *sy[i];
        }
        vec3 edge = 1.0-sqrt(colx*colx+coly*coly);
        vec4 color = texture(screenTexture, TexCoords);
        float factor = toonify(max(color.r, max(color.g, color.b)));
        FragColor = vec4(factor*(color.rgb+edge.rgb), color.a) ;
    }
    else if(doPixelationShading)
    {
        float Pixels = 2048.0;
        float dx = 15.0 * (1.0 / Pixels);
        float dy = 10.0 * (1.0 / Pixels);
        vec2 Coord = vec2(dx * floor(TexCoords.x / dx),
                          dy * floor(TexCoords.y / dy));

        FragColor = texture(screenTexture, Coord);
    }
    else
    {
        FragColor = texture(screenTexture, TexCoords);
    }

    FragColor.rgb = toneMapping(FragColor.rgb);
    FragColor.rgb = gammaCorrection(FragColor.rgb);


}