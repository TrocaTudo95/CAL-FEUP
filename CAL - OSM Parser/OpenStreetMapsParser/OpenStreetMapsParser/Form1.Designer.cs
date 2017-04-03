/* ========================================================================= *
 * Name        : Open Street Maps Parser
 * Author      : Nuno Filipe Sousa da Silva nufil.silva@gmail.com
 * Version     : 1.0
 * Copyright   : Nuno Filipe Sousa da Silva
 * Description : 
 * ========================================================================= */
namespace OpenStreetMapsParser
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panel1 = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.destNumEdgesLabel = new System.Windows.Forms.Label();
            this.destNumNodesLabel = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.destMinLongitudeLabel = new System.Windows.Forms.Label();
            this.destMinLatitudeLabel = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.destMaxLongitudeLabel = new System.Windows.Forms.Label();
            this.destMaxLatitudeLabel = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.produceMapFileButton = new System.Windows.Forms.Button();
            this.produceNewMapButton = new System.Windows.Forms.Button();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.destMinLongitudeTextBox = new System.Windows.Forms.TextBox();
            this.destMinLatitudeTextBox = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.destMaxLongitudeTextBox = new System.Windows.Forms.TextBox();
            this.destMaxLatitudeTextBox = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.UseRealNodesValueCheckBox = new System.Windows.Forms.CheckBox();
            this.fileNameLabel = new System.Windows.Forms.Label();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.origNumEdgesLabel = new System.Windows.Forms.Label();
            this.origNumNodesLabel = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.analyseOriginalMapButton = new System.Windows.Forms.Button();
            this.openStreetMapFileButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.origMinLongitudeLabel = new System.Windows.Forms.Label();
            this.origMinLatitudeLabel = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.origMaxLongitudeLabel = new System.Windows.Forms.Label();
            this.origMaxLatitudeLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.pictureBox1);
            this.panel1.Controls.Add(this.groupBox3);
            this.panel1.Controls.Add(this.groupBox10);
            this.panel1.Controls.Add(this.groupBox5);
            this.panel1.Location = new System.Drawing.Point(12, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(711, 563);
            this.panel1.TabIndex = 1;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = global::OpenStreetMapsParser.Properties.Resources.Logo_FEUP;
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox1.Location = new System.Drawing.Point(495, 11);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(213, 152);
            this.pictureBox1.TabIndex = 13;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.groupBox4);
            this.groupBox3.Controls.Add(this.groupBox7);
            this.groupBox3.Controls.Add(this.groupBox11);
            this.groupBox3.Location = new System.Drawing.Point(3, 336);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(479, 224);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "New Map";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.destNumEdgesLabel);
            this.groupBox4.Controls.Add(this.destNumNodesLabel);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Location = new System.Drawing.Point(20, 132);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(435, 85);
            this.groupBox4.TabIndex = 4;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Statistics";
            // 
            // destNumEdgesLabel
            // 
            this.destNumEdgesLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destNumEdgesLabel.Location = new System.Drawing.Point(121, 51);
            this.destNumEdgesLabel.Name = "destNumEdgesLabel";
            this.destNumEdgesLabel.Size = new System.Drawing.Size(296, 20);
            this.destNumEdgesLabel.TabIndex = 6;
            // 
            // destNumNodesLabel
            // 
            this.destNumNodesLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destNumNodesLabel.Location = new System.Drawing.Point(122, 25);
            this.destNumNodesLabel.Name = "destNumNodesLabel";
            this.destNumNodesLabel.Size = new System.Drawing.Size(295, 20);
            this.destNumNodesLabel.TabIndex = 5;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(17, 51);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(92, 13);
            this.label7.TabIndex = 1;
            this.label7.Text = "Number of Edges:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(16, 29);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(93, 13);
            this.label8.TabIndex = 0;
            this.label8.Text = "Number of Nodes:";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.destMinLongitudeLabel);
            this.groupBox7.Controls.Add(this.destMinLatitudeLabel);
            this.groupBox7.Controls.Add(this.label23);
            this.groupBox7.Controls.Add(this.label24);
            this.groupBox7.Location = new System.Drawing.Point(20, 19);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(200, 100);
            this.groupBox7.TabIndex = 2;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Min";
            // 
            // destMinLongitudeLabel
            // 
            this.destMinLongitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destMinLongitudeLabel.Location = new System.Drawing.Point(83, 61);
            this.destMinLongitudeLabel.Name = "destMinLongitudeLabel";
            this.destMinLongitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.destMinLongitudeLabel.TabIndex = 5;
            // 
            // destMinLatitudeLabel
            // 
            this.destMinLatitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destMinLatitudeLabel.Location = new System.Drawing.Point(83, 30);
            this.destMinLatitudeLabel.Name = "destMinLatitudeLabel";
            this.destMinLatitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.destMinLatitudeLabel.TabIndex = 4;
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(14, 66);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(54, 13);
            this.label23.TabIndex = 1;
            this.label23.Text = "Longitude";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(14, 31);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(45, 13);
            this.label24.TabIndex = 0;
            this.label24.Text = "Latitude";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.destMaxLongitudeLabel);
            this.groupBox11.Controls.Add(this.destMaxLatitudeLabel);
            this.groupBox11.Controls.Add(this.label27);
            this.groupBox11.Controls.Add(this.label28);
            this.groupBox11.Location = new System.Drawing.Point(255, 19);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(200, 100);
            this.groupBox11.TabIndex = 3;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Max";
            // 
            // destMaxLongitudeLabel
            // 
            this.destMaxLongitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destMaxLongitudeLabel.Location = new System.Drawing.Point(84, 61);
            this.destMaxLongitudeLabel.Name = "destMaxLongitudeLabel";
            this.destMaxLongitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.destMaxLongitudeLabel.TabIndex = 7;
            // 
            // destMaxLatitudeLabel
            // 
            this.destMaxLatitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.destMaxLatitudeLabel.Location = new System.Drawing.Point(84, 30);
            this.destMaxLatitudeLabel.Name = "destMaxLatitudeLabel";
            this.destMaxLatitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.destMaxLatitudeLabel.TabIndex = 6;
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(15, 64);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(54, 13);
            this.label27.TabIndex = 1;
            this.label27.Text = "Longitude";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(15, 33);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(45, 13);
            this.label28.TabIndex = 0;
            this.label28.Text = "Latitude";
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.produceMapFileButton);
            this.groupBox10.Controls.Add(this.produceNewMapButton);
            this.groupBox10.Controls.Add(this.groupBox8);
            this.groupBox10.Controls.Add(this.groupBox9);
            this.groupBox10.Location = new System.Drawing.Point(495, 169);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(213, 384);
            this.groupBox10.TabIndex = 11;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "Operations";
            // 
            // produceMapFileButton
            // 
            this.produceMapFileButton.Enabled = false;
            this.produceMapFileButton.Location = new System.Drawing.Point(7, 296);
            this.produceMapFileButton.Name = "produceMapFileButton";
            this.produceMapFileButton.Size = new System.Drawing.Size(200, 51);
            this.produceMapFileButton.TabIndex = 12;
            this.produceMapFileButton.Text = "Produce Map File";
            this.produceMapFileButton.UseVisualStyleBackColor = true;
            this.produceMapFileButton.Click += new System.EventHandler(this.produceMapFileButton_Click);
            // 
            // produceNewMapButton
            // 
            this.produceNewMapButton.Enabled = false;
            this.produceNewMapButton.Location = new System.Drawing.Point(6, 238);
            this.produceNewMapButton.Name = "produceNewMapButton";
            this.produceNewMapButton.Size = new System.Drawing.Size(200, 51);
            this.produceNewMapButton.TabIndex = 11;
            this.produceNewMapButton.Text = "Produce new map statistics";
            this.produceNewMapButton.UseVisualStyleBackColor = true;
            this.produceNewMapButton.Click += new System.EventHandler(this.produceNewMapButton_Click);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.destMinLongitudeTextBox);
            this.groupBox8.Controls.Add(this.destMinLatitudeTextBox);
            this.groupBox8.Controls.Add(this.label9);
            this.groupBox8.Controls.Add(this.label10);
            this.groupBox8.Location = new System.Drawing.Point(6, 25);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(200, 100);
            this.groupBox8.TabIndex = 9;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Min";
            // 
            // destMinLongitudeTextBox
            // 
            this.destMinLongitudeTextBox.Location = new System.Drawing.Point(83, 59);
            this.destMinLongitudeTextBox.Name = "destMinLongitudeTextBox";
            this.destMinLongitudeTextBox.Size = new System.Drawing.Size(100, 20);
            this.destMinLongitudeTextBox.TabIndex = 3;
            // 
            // destMinLatitudeTextBox
            // 
            this.destMinLatitudeTextBox.Location = new System.Drawing.Point(83, 28);
            this.destMinLatitudeTextBox.Name = "destMinLatitudeTextBox";
            this.destMinLatitudeTextBox.Size = new System.Drawing.Size(100, 20);
            this.destMinLatitudeTextBox.TabIndex = 2;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(14, 66);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(54, 13);
            this.label9.TabIndex = 1;
            this.label9.Text = "Longitude";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(14, 31);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(45, 13);
            this.label10.TabIndex = 0;
            this.label10.Text = "Latitude";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.destMaxLongitudeTextBox);
            this.groupBox9.Controls.Add(this.destMaxLatitudeTextBox);
            this.groupBox9.Controls.Add(this.label11);
            this.groupBox9.Controls.Add(this.label12);
            this.groupBox9.Location = new System.Drawing.Point(6, 131);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(200, 100);
            this.groupBox9.TabIndex = 10;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Max";
            // 
            // destMaxLongitudeTextBox
            // 
            this.destMaxLongitudeTextBox.Location = new System.Drawing.Point(82, 61);
            this.destMaxLongitudeTextBox.Name = "destMaxLongitudeTextBox";
            this.destMaxLongitudeTextBox.Size = new System.Drawing.Size(100, 20);
            this.destMaxLongitudeTextBox.TabIndex = 3;
            // 
            // destMaxLatitudeTextBox
            // 
            this.destMaxLatitudeTextBox.Location = new System.Drawing.Point(82, 30);
            this.destMaxLatitudeTextBox.Name = "destMaxLatitudeTextBox";
            this.destMaxLatitudeTextBox.Size = new System.Drawing.Size(100, 20);
            this.destMaxLatitudeTextBox.TabIndex = 2;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(15, 64);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(54, 13);
            this.label11.TabIndex = 1;
            this.label11.Text = "Longitude";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(15, 33);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(45, 13);
            this.label12.TabIndex = 0;
            this.label12.Text = "Latitude";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.UseRealNodesValueCheckBox);
            this.groupBox5.Controls.Add(this.fileNameLabel);
            this.groupBox5.Controls.Add(this.groupBox6);
            this.groupBox5.Controls.Add(this.analyseOriginalMapButton);
            this.groupBox5.Controls.Add(this.openStreetMapFileButton);
            this.groupBox5.Controls.Add(this.groupBox1);
            this.groupBox5.Controls.Add(this.groupBox2);
            this.groupBox5.Location = new System.Drawing.Point(3, 3);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(479, 327);
            this.groupBox5.TabIndex = 7;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Original Map";
            // 
            // UseRealNodesValueCheckBox
            // 
            this.UseRealNodesValueCheckBox.AutoSize = true;
            this.UseRealNodesValueCheckBox.Location = new System.Drawing.Point(20, 57);
            this.UseRealNodesValueCheckBox.Name = "UseRealNodesValueCheckBox";
            this.UseRealNodesValueCheckBox.Size = new System.Drawing.Size(407, 17);
            this.UseRealNodesValueCheckBox.TabIndex = 6;
            this.UseRealNodesValueCheckBox.Text = "Analyse the real number of nodes of roads - (Needs much more memory and time)";
            this.UseRealNodesValueCheckBox.UseVisualStyleBackColor = true;
            // 
            // fileNameLabel
            // 
            this.fileNameLabel.BackColor = System.Drawing.SystemColors.Window;
            this.fileNameLabel.Location = new System.Drawing.Point(20, 30);
            this.fileNameLabel.Name = "fileNameLabel";
            this.fileNameLabel.Size = new System.Drawing.Size(286, 20);
            this.fileNameLabel.TabIndex = 5;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.origNumEdgesLabel);
            this.groupBox6.Controls.Add(this.origNumNodesLabel);
            this.groupBox6.Controls.Add(this.label18);
            this.groupBox6.Controls.Add(this.label17);
            this.groupBox6.Location = new System.Drawing.Point(20, 229);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(435, 85);
            this.groupBox6.TabIndex = 4;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "Statistics";
            // 
            // origNumEdgesLabel
            // 
            this.origNumEdgesLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origNumEdgesLabel.Location = new System.Drawing.Point(121, 51);
            this.origNumEdgesLabel.Name = "origNumEdgesLabel";
            this.origNumEdgesLabel.Size = new System.Drawing.Size(296, 20);
            this.origNumEdgesLabel.TabIndex = 6;
            // 
            // origNumNodesLabel
            // 
            this.origNumNodesLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origNumNodesLabel.Location = new System.Drawing.Point(122, 25);
            this.origNumNodesLabel.Name = "origNumNodesLabel";
            this.origNumNodesLabel.Size = new System.Drawing.Size(295, 20);
            this.origNumNodesLabel.TabIndex = 5;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(17, 51);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(92, 13);
            this.label18.TabIndex = 1;
            this.label18.Text = "Number of Edges:";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(16, 29);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(93, 13);
            this.label17.TabIndex = 0;
            this.label17.Text = "Number of Nodes:";
            // 
            // analyseOriginalMapButton
            // 
            this.analyseOriginalMapButton.Enabled = false;
            this.analyseOriginalMapButton.Location = new System.Drawing.Point(20, 79);
            this.analyseOriginalMapButton.Name = "analyseOriginalMapButton";
            this.analyseOriginalMapButton.Size = new System.Drawing.Size(435, 27);
            this.analyseOriginalMapButton.TabIndex = 1;
            this.analyseOriginalMapButton.Text = "Analyse Original Map";
            this.analyseOriginalMapButton.UseVisualStyleBackColor = true;
            this.analyseOriginalMapButton.Click += new System.EventHandler(this.analyseOriginalMapButton_Click);
            // 
            // openStreetMapFileButton
            // 
            this.openStreetMapFileButton.Location = new System.Drawing.Point(312, 29);
            this.openStreetMapFileButton.Name = "openStreetMapFileButton";
            this.openStreetMapFileButton.Size = new System.Drawing.Size(143, 22);
            this.openStreetMapFileButton.TabIndex = 0;
            this.openStreetMapFileButton.Text = "Open OpenStreetMap File";
            this.openStreetMapFileButton.UseVisualStyleBackColor = true;
            this.openStreetMapFileButton.Click += new System.EventHandler(this.openStreetMapFileButton_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.origMinLongitudeLabel);
            this.groupBox1.Controls.Add(this.origMinLatitudeLabel);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(20, 116);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(200, 100);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Min";
            // 
            // origMinLongitudeLabel
            // 
            this.origMinLongitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origMinLongitudeLabel.Location = new System.Drawing.Point(83, 61);
            this.origMinLongitudeLabel.Name = "origMinLongitudeLabel";
            this.origMinLongitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.origMinLongitudeLabel.TabIndex = 5;
            // 
            // origMinLatitudeLabel
            // 
            this.origMinLatitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origMinLatitudeLabel.Location = new System.Drawing.Point(83, 30);
            this.origMinLatitudeLabel.Name = "origMinLatitudeLabel";
            this.origMinLatitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.origMinLatitudeLabel.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 66);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Longitude";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 31);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Latitude";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.origMaxLongitudeLabel);
            this.groupBox2.Controls.Add(this.origMaxLatitudeLabel);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new System.Drawing.Point(255, 116);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(200, 100);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Max";
            // 
            // origMaxLongitudeLabel
            // 
            this.origMaxLongitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origMaxLongitudeLabel.Location = new System.Drawing.Point(84, 61);
            this.origMaxLongitudeLabel.Name = "origMaxLongitudeLabel";
            this.origMaxLongitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.origMaxLongitudeLabel.TabIndex = 7;
            // 
            // origMaxLatitudeLabel
            // 
            this.origMaxLatitudeLabel.BackColor = System.Drawing.SystemColors.Window;
            this.origMaxLatitudeLabel.Location = new System.Drawing.Point(84, 30);
            this.origMaxLatitudeLabel.Name = "origMaxLatitudeLabel";
            this.origMaxLatitudeLabel.Size = new System.Drawing.Size(98, 20);
            this.origMaxLatitudeLabel.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(15, 64);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(54, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "Longitude";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(15, 33);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(45, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Latitude";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(735, 587);
            this.Controls.Add(this.panel1);
            this.Name = "Form1";
            this.Text = "Open Street Maps Parser";
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label destNumEdgesLabel;
        private System.Windows.Forms.Label destNumNodesLabel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Label destMinLongitudeLabel;
        private System.Windows.Forms.Label destMinLatitudeLabel;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label destMaxLongitudeLabel;
        private System.Windows.Forms.Label destMaxLatitudeLabel;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.Button produceMapFileButton;
        private System.Windows.Forms.Button produceNewMapButton;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.TextBox destMinLongitudeTextBox;
        private System.Windows.Forms.TextBox destMinLatitudeTextBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.TextBox destMaxLongitudeTextBox;
        private System.Windows.Forms.TextBox destMaxLatitudeTextBox;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Label origNumEdgesLabel;
        private System.Windows.Forms.Label origNumNodesLabel;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button analyseOriginalMapButton;
        private System.Windows.Forms.Button openStreetMapFileButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label origMinLongitudeLabel;
        private System.Windows.Forms.Label origMinLatitudeLabel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label origMaxLongitudeLabel;
        private System.Windows.Forms.Label origMaxLatitudeLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label fileNameLabel;
        private System.Windows.Forms.CheckBox UseRealNodesValueCheckBox;
    }
}

