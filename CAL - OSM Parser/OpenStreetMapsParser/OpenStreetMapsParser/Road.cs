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
    class Road
    {
        long id;
        string name;
        bool twoWay;
        List<long> lineID;

        public Road(long id, string name, bool twoWay)
        {
            this.id=id;
            this.name = name;
            this.twoWay = twoWay;
            lineID = new List<long>();
        }

        public long getId()
        {
            return id;
        }

        public string getName()
        {
            return name;
        }

        public bool isTwoWay()
        {
            return twoWay;
        }

        public void addLine(long lineID)
        {
            bool found = false;
            foreach (long e in this.lineID)
            {
                if (e.Equals(lineID))
                {
                    found = true;
                }
            }
            if (!found)
            {
                this.lineID.Add(lineID);
            }
        }

        public List<long> getLine()
        {
            return this.lineID;
        }
    }
}
