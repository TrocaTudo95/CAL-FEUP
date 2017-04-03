/* ========================================================================= *
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
    class PlateCareePaintMapModel
    {
        static public PointF GPSCoordinatesToProjection(PointF GPSCoordinates)
        {
            //Convert the GPSCoordinates Angle from degrees to radians
            double radianX = GPSCoordinates.X * (Math.PI / 180);
            double radianY = GPSCoordinates.Y * (Math.PI / 180);

            //Calculate the projection coordinates
            PointF projectionCoordinates = new PointF();
            projectionCoordinates.X = (float)radianX;
            projectionCoordinates.Y = (float)radianY;

            return projectionCoordinates;
        }
    }
}
