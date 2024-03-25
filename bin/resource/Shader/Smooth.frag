uniform sampler2D texture;

void main()
{
    vec2 offAntiX = vec2(0.0005, 0.0);
    vec2 offAntiY = vec2(0.0, 0.0005);


    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiY * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiY * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX * 1.5 + offAntiY * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy + offAntiX * 1.5 - offAntiY * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX * 1.5 + offAntiY * 1.5)
           + texture2D(texture, gl_TexCoord[0].xy - offAntiX * 1.5 - offAntiY * 1.5);

    gl_FragColor =  gl_Color * (pixel / 17.0);
}