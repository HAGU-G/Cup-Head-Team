uniform sampler2D texture;

void main()
{
    vec2 offr = vec2(0.0,0.002);
    vec2 offg = vec2(0.0,-0.002);
    vec2 offb = vec2(-0.002,0.0);
    vec2 offAntiX = vec2(0.0005, 0.0);
    vec2 offAntiY = vec2(0.0, 0.0005);


    vec4 r = texture2D(texture, gl_TexCoord[0].xy + offr) * 12.0
           + texture2D(texture, gl_TexCoord[0].xy + offr + offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offr + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offr - offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offr - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offr + offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offr + offAntiY * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offr - offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offr - offAntiY * 2.0);

    vec4 g = texture2D(texture, gl_TexCoord[0].xy + offg) * 12.0
           + texture2D(texture, gl_TexCoord[0].xy + offg + offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offg + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offg - offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offg - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offg + offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offg + offAntiY * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offg - offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offg - offAntiY * 2.0);

    vec4 b = texture2D(texture, gl_TexCoord[0].xy + offb) * 12.0
           + texture2D(texture, gl_TexCoord[0].xy + offb + offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offb + offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offb - offAntiX)
           + texture2D(texture, gl_TexCoord[0].xy + offb - offAntiY)
           + texture2D(texture, gl_TexCoord[0].xy + offb + offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offb + offAntiY * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offb - offAntiX * 2.0)
           + texture2D(texture, gl_TexCoord[0].xy + offb - offAntiY * 2.0);

    vec4 pixel = vec4(r.r, g.g, b.b, r.a + b.a + g.a);
    gl_FragColor =  gl_Color * ( pixel / 20.0);
}