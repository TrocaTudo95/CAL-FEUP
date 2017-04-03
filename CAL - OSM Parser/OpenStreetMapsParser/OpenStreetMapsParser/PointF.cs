﻿/* ========================================================================= *
 * Name        : Open Street Maps Parser
 * Author      : Nuno Filipe Sousa da Silva nufil.silva@gmail.com
 * Version     : 1.0
 * Copyright   : Nuno Filipe Sousa da Silva
 * Description : 
 * ========================================================================= */
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace OpenStreetMapsParser
{
    class PointF
    {
        public float X;
        public float Y;

        public PointF()
        {
            this.X = (float)0;
            this.Y = (float)0;
        }

        public PointF(float X, float Y)
        {
            this.X = X;
            this.Y = Y;
        }
    }
}
