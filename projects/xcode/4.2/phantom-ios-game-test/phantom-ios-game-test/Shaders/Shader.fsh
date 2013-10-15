//
//  Shader.fsh
//  phantom-ios-game-test
//
//  Created by Lion User on 29/02/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
