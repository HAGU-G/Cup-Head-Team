uniform sampler2D texture;

void main()
{
    vec2 offr = vec2(0.0,0.0015);
    vec2 offg = vec2(0.0,-0.0015);
    vec2 offb = vec2(-0.0015,0.0);


    vec4 r = texture2D(texture, gl_TexCoord[0].xy + offr);

    vec4 g = texture2D(texture, gl_TexCoord[0].xy + offg);

    vec4 b = texture2D(texture, gl_TexCoord[0].xy + offb);

    vec4 pixel = vec4(r.r, g.g, b.b, r.a + b.a + g.a);
    gl_FragColor =  gl_Color * ( pixel);
}