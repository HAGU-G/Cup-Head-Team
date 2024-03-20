uniform sampler2D texture;

void main()
{

    vec4 pixel = gl_Color * texture2D(texture, gl_TexCoord[0].xy);
    pixel.rgb += (1.0 - pixel.rgb) / 3.0;
    gl_FragColor = pixel;
}