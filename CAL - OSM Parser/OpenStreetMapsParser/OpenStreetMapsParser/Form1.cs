using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Globalization;

namespace OpenStreetMapsParser
{
    public partial class Form1 : Form
    {
        Map map;
        public Form1()
        {
            InitializeComponent();
        }

        private void openStreetMapFileButton_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.Filter = "osm maps (*.osm)|*.osm";
            this.openFileDialog1.FileName = "";
            this.openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            this.origNumNodesLabel.Text = "";
            this.origNumEdgesLabel.Text = "";

            this.origMaxLatitudeLabel.Text = "";
            this.origMaxLongitudeLabel.Text = "";
            this.origMinLatitudeLabel.Text = "";
            this.origMinLongitudeLabel.Text = "";

            this.destMaxLatitudeTextBox.Text = "";
            this.destMaxLongitudeTextBox.Text = "";
            this.destMinLatitudeTextBox.Text = "";
            this.destMinLongitudeTextBox.Text = "";

            this.destMaxLatitudeLabel.Text = "";
            this.destMaxLongitudeLabel.Text = "";
            this.destMinLatitudeLabel.Text = "";
            this.destMinLongitudeLabel.Text = "";
            this.destNumNodesLabel.Text = "";
            this.destNumEdgesLabel.Text = "";

            this.fileNameLabel.Text = this.openFileDialog1.FileName;
            this.map = new Map(this.openFileDialog1.FileName);
            this.openStreetMapFileButton.Enabled = true;
            this.analyseOriginalMapButton.Enabled = true;
            this.produceMapFileButton.Enabled = false;
            this.produceNewMapButton.Enabled = false;


            
        }


        static void analyseOriginalMapThread()
        {
            for (int i = 0; i < 1000; i++) Console.Write("y");
        }

        private void analyseOriginalMapButton_Click(object sender, EventArgs e)
        {
            if (this.map!=null)
            {
                try
                {
                    this.origNumNodesLabel.Text = "";
                    this.origNumEdgesLabel.Text = "";

                    this.origMaxLatitudeLabel.Text = "";
                    this.origMaxLongitudeLabel.Text = "";
                    this.origMinLatitudeLabel.Text = "";
                    this.origMinLongitudeLabel.Text = "";

                    this.destMaxLatitudeTextBox.Text = "";
                    this.destMaxLongitudeTextBox.Text = "";
                    this.destMinLatitudeTextBox.Text = "";
                    this.destMinLongitudeTextBox.Text = "";

                    this.destMaxLatitudeLabel.Text = "";
                    this.destMaxLongitudeLabel.Text = "";
                    this.destMinLatitudeLabel.Text = "";
                    this.destMinLongitudeLabel.Text = "";
                    this.destNumNodesLabel.Text = "";
                    this.destNumEdgesLabel.Text = "";

                    this.openStreetMapFileButton.Enabled = false;
                    this.analyseOriginalMapButton.Enabled = false;
                    this.produceNewMapButton.Enabled = false;
                    this.produceMapFileButton.Enabled = false;

                    this.UseWaitCursor = true;
                    this.Refresh();
                    this.map.analyseOpenStreetMap(this.UseRealNodesValueCheckBox.Checked);
                    this.origNumNodesLabel.Text = this.map.getNumOfNodes().ToString(CultureInfo.InvariantCulture);
                    this.origNumEdgesLabel.Text = this.map.getNumOfEdges().ToString(CultureInfo.InvariantCulture);

                    this.origMaxLatitudeLabel.Text = this.map.getMaxLat().ToString(CultureInfo.InvariantCulture);
                    this.origMaxLongitudeLabel.Text = this.map.getMaxLon().ToString(CultureInfo.InvariantCulture);
                    this.origMinLatitudeLabel.Text = this.map.getMinLat().ToString(CultureInfo.InvariantCulture);
                    this.origMinLongitudeLabel.Text = this.map.getMinLon().ToString(CultureInfo.InvariantCulture);

                    this.destMaxLatitudeTextBox.Text = this.map.getMaxLat().ToString(CultureInfo.InvariantCulture);
                    this.destMaxLongitudeTextBox.Text = this.map.getMaxLon().ToString(CultureInfo.InvariantCulture);
                    this.destMinLatitudeTextBox.Text = this.map.getMinLat().ToString(CultureInfo.InvariantCulture);
                    this.destMinLongitudeTextBox.Text = this.map.getMinLon().ToString(CultureInfo.InvariantCulture);




                    this.UseWaitCursor = false;


                    this.openStreetMapFileButton.Enabled = true;
                    this.analyseOriginalMapButton.Enabled = true;
                    this.produceNewMapButton.Enabled = true;
                    this.produceMapFileButton.Enabled = false;
                }
                catch (Exception)
                {
                    this.analyseOriginalMapButton.Enabled = false;
                    this.produceMapFileButton.Enabled = false;
                    this.produceNewMapButton.Enabled = false;
                    MessageBox.Show("An error occured! Please contact an administrator");
                }
            }
            else
            {
                this.analyseOriginalMapButton.Enabled = false;
                this.produceMapFileButton.Enabled = false;
                this.produceNewMapButton.Enabled = false;
                MessageBox.Show("An error occured! Please contact an administrator");
            }
        }

        private void produceNewMapButton_Click(object sender, EventArgs e)
        {
            if (this.map != null)
            {
                if (this.destMinLatitudeTextBox.Text != "" && this.destMinLongitudeTextBox.Text != "" && this.destMaxLatitudeTextBox.Text != "" && this.destMaxLongitudeTextBox.Text != "")
                {
                    try
                    {
                        this.openStreetMapFileButton.Enabled = false;
                        this.analyseOriginalMapButton.Enabled = false;
                        this.produceNewMapButton.Enabled = false;
                        this.produceMapFileButton.Enabled = false;

                        this.destMaxLatitudeLabel.Text = "";
                        this.destMaxLongitudeLabel.Text = "";
                        this.destMinLatitudeLabel.Text = "";
                        this.destMinLongitudeLabel.Text = "";
                        this.destNumNodesLabel.Text = "";
                        this.destNumEdgesLabel.Text = "";

                        float minlat = float.Parse(this.destMinLatitudeTextBox.Text, CultureInfo.InvariantCulture);
                        float minlon = float.Parse(this.destMinLongitudeTextBox.Text, CultureInfo.InvariantCulture);
                        float maxlat = float.Parse(this.destMaxLatitudeTextBox.Text, CultureInfo.InvariantCulture);
                        float maxlon = float.Parse(this.destMaxLongitudeTextBox.Text, CultureInfo.InvariantCulture);
                        this.map.analyseOpenStreetMapCropped(minlat,minlon, maxlat, maxlon);

                        this.destMaxLatitudeLabel.Text = this.map.getCroppedMaxLat().ToString(CultureInfo.InvariantCulture);
                        this.destMaxLongitudeLabel.Text = this.map.getCroppedMaxLon().ToString(CultureInfo.InvariantCulture);
                        this.destMinLatitudeLabel.Text = this.map.getCroppedMinLat().ToString(CultureInfo.InvariantCulture);
                        this.destMinLongitudeLabel.Text = this.map.getCroppedMinLon().ToString(CultureInfo.InvariantCulture);
                        this.destNumNodesLabel.Text = this.map.getCroppedNumOfNodes().ToString(CultureInfo.InvariantCulture);
                        this.destNumEdgesLabel.Text = this.map.getCroppedNumOfEdges().ToString(CultureInfo.InvariantCulture);

                        this.openStreetMapFileButton.Enabled = true;
                        this.analyseOriginalMapButton.Enabled = true;
                        this.produceNewMapButton.Enabled = true;
                        this.produceMapFileButton.Enabled = true;
                    }
                    catch (FormatException)
                    {
                        MessageBox.Show("The latitude or longitude values are in a wrong format.");
                    }
                    catch (Exception)
                    {
                        this.analyseOriginalMapButton.Enabled = false;
                        this.produceMapFileButton.Enabled = false;
                        this.produceNewMapButton.Enabled = false;
                        MessageBox.Show("An error occured! Please contact an administrator");
                    }
                }
                else
                {
                    MessageBox.Show("Invalid latitude or longitude values!");
                }
            }
            else
            {
                this.analyseOriginalMapButton.Enabled = false;
                this.produceMapFileButton.Enabled = false;
                this.produceNewMapButton.Enabled = false;
                MessageBox.Show("An error occured! Please contact an administrator");
            }
        }

        private void produceMapFileButton_Click(object sender, EventArgs e)
        {
            this.saveFileDialog1.Title = "Select the file to save the Nodes";
            this.saveFileDialog1.FileName = "";
            this.saveFileDialog1.Filter = "Text Documents (*.txt)|*.txt";
            this.saveFileDialog1.DefaultExt = "txt";
            DialogResult res = this.saveFileDialog1.ShowDialog();
           
            string fileNameNodes = this.saveFileDialog1.FileName;

            if (res != DialogResult.Cancel)
            if (fileNameNodes != "")
            {
                this.saveFileDialog1.Title = "Select the file to save the Roads";
                this.saveFileDialog1.FileName = "";
                res = this.saveFileDialog1.ShowDialog();
                string fileNameRoads = this.saveFileDialog1.FileName;
                if (res != DialogResult.Cancel)
                if (fileNameRoads != "")
                {
                    this.saveFileDialog1.Title = "Select the file to save the SubRoads";
                    this.saveFileDialog1.FileName = "";
                    res = this.saveFileDialog1.ShowDialog();
                    string fileNameSubRoads = this.saveFileDialog1.FileName;
                    if (res != DialogResult.Cancel)
                    if (fileNameSubRoads != "")
                    {
                        this.saveFileDialog1.Title = "Select the file to save the Metro per Pixel";
                        this.saveFileDialog1.FileName = "";
                        res = this.saveFileDialog1.ShowDialog();
                        string fileDistance = this.saveFileDialog1.FileName;
                        if (res != DialogResult.Cancel)
                        if (fileDistance != "")
                        {
                            if (this.destMinLatitudeTextBox.Text != "" && this.destMinLongitudeTextBox.Text != "" && this.destMaxLatitudeTextBox.Text != "" && this.destMaxLongitudeTextBox.Text != "")
                            {
                                try
                                {
                                    this.openStreetMapFileButton.Enabled = false;
                                    this.analyseOriginalMapButton.Enabled = false;
                                    this.produceNewMapButton.Enabled = false;
                                    this.produceMapFileButton.Enabled = false;

                                    float minlat = float.Parse(this.destMinLatitudeTextBox.Text, CultureInfo.InvariantCulture);
                                    float minlon = float.Parse(this.destMinLongitudeTextBox.Text, CultureInfo.InvariantCulture);
                                    float maxlat = float.Parse(this.destMaxLatitudeTextBox.Text, CultureInfo.InvariantCulture);
                                    float maxlon = float.Parse(this.destMaxLongitudeTextBox.Text, CultureInfo.InvariantCulture);

                                    this.map.saveOpenStreetMapCropped(minlat, minlon, maxlat, maxlon, fileNameNodes, fileNameRoads, fileNameSubRoads, fileDistance);

                                    this.openStreetMapFileButton.Enabled = true;
                                    this.analyseOriginalMapButton.Enabled = true;
                                    this.produceNewMapButton.Enabled = true;
                                    this.produceMapFileButton.Enabled = true;
                                }
                                catch (FormatException)
                                {
                                    MessageBox.Show("The latitude or longitude values are in a wrong format.");
                                }
                                catch (Exception)
                                {
                                    MessageBox.Show("An error occured! Please contact an administrator");
                                }
                             }
                             else
                             {
                                MessageBox.Show("Invalid latitude or longitude values!");
                             }
                        }
                        else
                        {
                            MessageBox.Show("Invalid distance filename!");
                        }
                    }
                    else
                    {
                        MessageBox.Show("Invalid subroads filename!");
                    }
                }
                else
                {
                    MessageBox.Show("Invalid roads filename!");
                }
            }
            else
            {
                MessageBox.Show("Invalid nodes filename!");
            }
        }
    }
}
