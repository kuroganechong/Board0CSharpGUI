namespace WaferProject
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;
        
        public static string password;
        
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.EnableSound = new System.Windows.Forms.CheckBox();
            this.Gamepad_CheckBox = new System.Windows.Forms.CheckBox();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.label89 = new System.Windows.Forms.Label();
            this.FireWatch_MaxTemp = new System.Windows.Forms.TextBox();
            this.ShouldWeStreamImage = new System.Windows.Forms.CheckBox();
            this.btHMfound_MCU = new System.Windows.Forms.Button();
            this.label67 = new System.Windows.Forms.Label();
            this.tbTemperaturmin = new System.Windows.Forms.TextBox();
            this.label68 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.tbTemperaturemax = new System.Windows.Forms.TextBox();
            this.GroupBoxControl_ChipSelection = new System.Windows.Forms.GroupBox();
            this.Button_BlueToothConnection = new System.Windows.Forms.Button();
            this.cbChipID = new System.Windows.Forms.ComboBox();
            this.label59 = new System.Windows.Forms.Label();
            this.GroupBoxControl_Setting = new System.Windows.Forms.GroupBox();
            this.TextRequestData = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.Button_Serial_OpenPorts = new System.Windows.Forms.Button();
            this.LabelBox_Serial_Status = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.CheckBox_BlueTooth_AutoLoad = new System.Windows.Forms.CheckBox();
            this.TextBox_BatteryVoltage = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.CheckBox_Serial_BaudRate = new System.Windows.Forms.ComboBox();
            this.CheckBox_SerialPorts = new System.Windows.Forms.ComboBox();
            this.tbReceviedData = new System.Windows.Forms.TextBox();
            this.GroupBoxControl_StimulationConfiguration = new System.Windows.Forms.GroupBox();
            this.cbRightPin = new System.Windows.Forms.ComboBox();
            this.cbLeftPin = new System.Windows.Forms.ComboBox();
            this.cbCercusRight = new System.Windows.Forms.ComboBox();
            this.cbCercusLeft = new System.Windows.Forms.ComboBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.AccelerationGroup = new System.Windows.Forms.GroupBox();
            this.label64 = new System.Windows.Forms.Label();
            this.label62 = new System.Windows.Forms.Label();
            this.GoFoward_Postion1 = new System.Windows.Forms.ComboBox();
            this.GoFoward_Postion2 = new System.Windows.Forms.ComboBox();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.label57 = new System.Windows.Forms.Label();
            this.TurnToLeft_V2 = new System.Windows.Forms.TextBox();
            this.label54 = new System.Windows.Forms.Label();
            this.TurnToLeft_V1 = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Period = new System.Windows.Forms.TextBox();
            this.label38 = new System.Windows.Forms.Label();
            this.label39 = new System.Windows.Forms.Label();
            this.label40 = new System.Windows.Forms.Label();
            this.label41 = new System.Windows.Forms.Label();
            this.label42 = new System.Windows.Forms.Label();
            this.label43 = new System.Windows.Forms.Label();
            this.label44 = new System.Windows.Forms.Label();
            this.TurnToLeft_Amplitude = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Toff2 = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Toff1 = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Ton2 = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Ton1 = new System.Windows.Forms.TextBox();
            this.TurnToLeft_Duration = new System.Windows.Forms.TextBox();
            this.Enable_TurnToLeft = new System.Windows.Forms.CheckBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label60 = new System.Windows.Forms.Label();
            this.TurnToRight_V2 = new System.Windows.Forms.TextBox();
            this.label56 = new System.Windows.Forms.Label();
            this.TurnToRight_V1 = new System.Windows.Forms.TextBox();
            this.TurnToRight_Period = new System.Windows.Forms.TextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.label27 = new System.Windows.Forms.Label();
            this.label26 = new System.Windows.Forms.Label();
            this.label24 = new System.Windows.Forms.Label();
            this.TurnToRight_Amplitude = new System.Windows.Forms.TextBox();
            this.TurnToRight_Toff2 = new System.Windows.Forms.TextBox();
            this.TurnToRight_Toff1 = new System.Windows.Forms.TextBox();
            this.TurnToRight_Ton2 = new System.Windows.Forms.TextBox();
            this.TurnToRight_Ton1 = new System.Windows.Forms.TextBox();
            this.TurnToRight_Duration = new System.Windows.Forms.TextBox();
            this.Enable_TurnToRight = new System.Windows.Forms.CheckBox();
            this.label25 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label58 = new System.Windows.Forms.Label();
            this.GoForward_V2 = new System.Windows.Forms.TextBox();
            this.label55 = new System.Windows.Forms.Label();
            this.GoForward_V1 = new System.Windows.Forms.TextBox();
            this.GoForward_Period = new System.Windows.Forms.TextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.label32 = new System.Windows.Forms.Label();
            this.label33 = new System.Windows.Forms.Label();
            this.label34 = new System.Windows.Forms.Label();
            this.label35 = new System.Windows.Forms.Label();
            this.label36 = new System.Windows.Forms.Label();
            this.label37 = new System.Windows.Forms.Label();
            this.GoForward_Amplitude = new System.Windows.Forms.TextBox();
            this.GoForward_Toff2 = new System.Windows.Forms.TextBox();
            this.GoForward_Toff1 = new System.Windows.Forms.TextBox();
            this.GoForward_Ton2 = new System.Windows.Forms.TextBox();
            this.GoForward_Ton1 = new System.Windows.Forms.TextBox();
            this.GoForward_Duration = new System.Windows.Forms.TextBox();
            this.Enable_Forward = new System.Windows.Forms.CheckBox();
            this.Stimulation = new System.Windows.Forms.GroupBox();
            this.label63 = new System.Windows.Forms.Label();
            this.bt_Stimulation_Right = new System.Windows.Forms.Button();
            this.bt_Stimulation_Forward = new System.Windows.Forms.Button();
            this.label61 = new System.Windows.Forms.Label();
            this.bt_Stimulation_Stop = new System.Windows.Forms.Button();
            this.bt_Stimulation_Left = new System.Windows.Forms.Button();
            this.AmbT = new System.Windows.Forms.TextBox();
            this.cbHTPASelect = new System.Windows.Forms.ComboBox();
            this.label71 = new System.Windows.Forms.Label();
            this.label75 = new System.Windows.Forms.Label();
            this.CheckBox_IsTheRoachConfined = new System.Windows.Forms.CheckBox();
            this.Button_ReadFlash = new System.Windows.Forms.Button();
            this.label51 = new System.Windows.Forms.Label();
            this.TextCalculatedLinearSpeed_Vicon = new System.Windows.Forms.TextBox();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.label101 = new System.Windows.Forms.Label();
            this.label53 = new System.Windows.Forms.Label();
            this.label52 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.TextCalculatedAngularSpeed_IMU = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.TextCalculatedLinearSpeed_IMU = new System.Windows.Forms.TextBox();
            this.TextCalculatedAngularSpeed_Vicon = new System.Windows.Forms.TextBox();
            this.GroupBoxControl_NavigationStartStop = new System.Windows.Forms.GroupBox();
            this.CheckClickToSaveFlash = new System.Windows.Forms.CheckBox();
            this.Navigation_Start = new System.Windows.Forms.Button();
            this.Navigation_Stop = new System.Windows.Forms.Button();
            this.SelectionOfGUITimer = new System.Windows.Forms.ComboBox();
            this.Button_UpdateGUITimer = new System.Windows.Forms.Button();
            this.TextBox_FileName = new System.Windows.Forms.TextBox();
            this.CheckClickToMute = new System.Windows.Forms.CheckBox();
            this.ClickToLogFile = new System.Windows.Forms.CheckBox();
            this.GroupBoxControl_StimulationIndicator = new System.Windows.Forms.GroupBox();
            this.StiSignal_Forward = new System.Windows.Forms.Button();
            this.StiSignal_Right = new System.Windows.Forms.Button();
            this.StiSignal_Left = new System.Windows.Forms.Button();
            this.Radio_RightCerciLeftSegment = new System.Windows.Forms.RadioButton();
            this.Radio_RightCerciRightSegment = new System.Windows.Forms.RadioButton();
            this.Radio_LeftCerciRightSegment = new System.Windows.Forms.RadioButton();
            this.Radio_LeftCerciLeftSegment = new System.Windows.Forms.RadioButton();
            this.Radio_BothSegment = new System.Windows.Forms.RadioButton();
            this.Radio_BothCerci = new System.Windows.Forms.RadioButton();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.PinConfiguration_CerciInside = new System.Windows.Forms.CheckBox();
            this.ClickToVaryV1V2 = new System.Windows.Forms.CheckBox();
            this.ReadyStimulation = new System.Windows.Forms.Button();
            this.GroupBoxControl_NavigationButton = new System.Windows.Forms.GroupBox();
            this.TestSpeed = new System.Windows.Forms.Button();
            this.label95 = new System.Windows.Forms.Label();
            this.SetupLongStimulus = new System.Windows.Forms.Button();
            this.comboBox11 = new System.Windows.Forms.ComboBox();
            this.SetupRight = new System.Windows.Forms.Button();
            this.SetupLeft = new System.Windows.Forms.Button();
            this.SetupAngleDistance = new System.Windows.Forms.Button();
            this.SetupForward = new System.Windows.Forms.Button();
            this.NormalStream = new System.Windows.Forms.Button();
            this.GroupBoxControl_NavigationTargets = new System.Windows.Forms.GroupBox();
            this.label13 = new System.Windows.Forms.Label();
            this.TargetY2 = new System.Windows.Forms.TextBox();
            this.TargetX2 = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.TextBox_CockroachY = new System.Windows.Forms.TextBox();
            this.TextBox_CockroachX = new System.Windows.Forms.TextBox();
            this.TargetY1 = new System.Windows.Forms.TextBox();
            this.TargetX1 = new System.Windows.Forms.TextBox();
            this.label87 = new System.Windows.Forms.Label();
            this.label84 = new System.Windows.Forms.Label();
            this.label86 = new System.Windows.Forms.Label();
            this.comboBox8 = new System.Windows.Forms.ComboBox();
            this.GroupBoxControl_NavigationParameters = new System.Windows.Forms.GroupBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.AngularSpeed_Vicon = new System.Windows.Forms.RadioButton();
            this.AngularSpeed_IMU = new System.Windows.Forms.RadioButton();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.LinearSpeed_Vicon = new System.Windows.Forms.RadioButton();
            this.LinearSpeed_IMU = new System.Windows.Forms.RadioButton();
            this.label15 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.Navigation_NoDataPoints = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.Navigation_AngularSpeedMethod = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.Navigation_ReactionTime = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.Navigation_UseEscapeMode = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.Navigation_AngularSpeed_Threshold = new System.Windows.Forms.TextBox();
            this.label48 = new System.Windows.Forms.Label();
            this.Navigation_AllowFreeWalkAfterSteering = new System.Windows.Forms.TextBox();
            this.label47 = new System.Windows.Forms.Label();
            this.Navigation_FreeTimeAfterSteering = new System.Windows.Forms.TextBox();
            this.label46 = new System.Windows.Forms.Label();
            this.Navigation_LongStimulusFreeTime2 = new System.Windows.Forms.TextBox();
            this.label100 = new System.Windows.Forms.Label();
            this.label90 = new System.Windows.Forms.Label();
            this.label98 = new System.Windows.Forms.Label();
            this.Navigation_Speed_Duration = new System.Windows.Forms.TextBox();
            this.Navigation_ControlRate = new System.Windows.Forms.TextBox();
            this.label99 = new System.Windows.Forms.Label();
            this.label77 = new System.Windows.Forms.Label();
            this.Navigation_LinearSpeed_Threshold = new System.Windows.Forms.TextBox();
            this.Navigation_Speed_Store = new System.Windows.Forms.TextBox();
            this.Navigation_FreeTime = new System.Windows.Forms.TextBox();
            this.label78 = new System.Windows.Forms.Label();
            this.Navigation_ForwardTime = new System.Windows.Forms.TextBox();
            this.label76 = new System.Windows.Forms.Label();
            this.Navigation_LongStimulusFreeTime = new System.Windows.Forms.TextBox();
            this.label74 = new System.Windows.Forms.Label();
            this.Navigation_LongStimulusForwardTime = new System.Windows.Forms.TextBox();
            this.label73 = new System.Windows.Forms.Label();
            this.Navigation_Distance = new System.Windows.Forms.TextBox();
            this.label70 = new System.Windows.Forms.Label();
            this.label72 = new System.Windows.Forms.Label();
            this.Navigation_Angle = new System.Windows.Forms.TextBox();
            this.comboBox5 = new System.Windows.Forms.ComboBox();
            this.groupBox17 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label69 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.Button_ViconConnection = new System.Windows.Forms.Button();
            this.TextBox_ViconStatus = new System.Windows.Forms.TextBox();
            this.Timer1 = new System.Windows.Forms.Timer(this.components);
            this.timer2 = new System.Windows.Forms.Timer(this.components);
            this.timer3 = new System.Windows.Forms.Timer(this.components);
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.IMU_Text_Speed = new System.Windows.Forms.TextBox();
            this.IMU_Text_Omega = new System.Windows.Forms.TextBox();
            this.label65 = new System.Windows.Forms.Label();
            this.label66 = new System.Windows.Forms.Label();
            this.IMU_Text_Gain = new System.Windows.Forms.TextBox();
            this.label50 = new System.Windows.Forms.Label();
            this.IMU_Text_SpeedZ = new System.Windows.Forms.TextBox();
            this.IMU_Text_SpeedY = new System.Windows.Forms.TextBox();
            this.IMU_Text_SpeedX = new System.Windows.Forms.TextBox();
            this.IMU_Text_AccZ = new System.Windows.Forms.TextBox();
            this.IMU_Text_AccY = new System.Windows.Forms.TextBox();
            this.IMU_Text_AccX = new System.Windows.Forms.TextBox();
            this.IMU_Text_Bias = new System.Windows.Forms.TextBox();
            this.IMU_Text_Roll = new System.Windows.Forms.TextBox();
            this.IMU_Text_Yaw = new System.Windows.Forms.TextBox();
            this.label49 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.IMU_Text_Pitch = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.label21 = new System.Windows.Forms.Label();
            this.label22 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.label45 = new System.Windows.Forms.Label();
            this.btHMfound_GUI = new System.Windows.Forms.Button();
            this.ShouldWeUseHumanDetectionGUI = new System.Windows.Forms.CheckBox();
            this.TextBoxHumanDetectionScoreMCU = new System.Windows.Forms.TextBox();
            this.textGUIThreshold = new System.Windows.Forms.TextBox();
            this.TextBoxScore = new System.Windows.Forms.TextBox();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.label85 = new System.Windows.Forms.Label();
            this.NumberOfPixelInRange = new System.Windows.Forms.TextBox();
            this.label83 = new System.Windows.Forms.Label();
            this.label79 = new System.Windows.Forms.Label();
            this.label81 = new System.Windows.Forms.Label();
            this.MaxOfRange = new System.Windows.Forms.TextBox();
            this.label82 = new System.Windows.Forms.Label();
            this.MinOfRange = new System.Windows.Forms.TextBox();
            this.MaxOfTemp = new System.Windows.Forms.TextBox();
            this.textMCUThreshold = new System.Windows.Forms.TextBox();
            this.label80 = new System.Windows.Forms.Label();
            this.MinOfTemp = new System.Windows.Forms.TextBox();
            this.DoWeUseOnBoardHumanDetection = new System.Windows.Forms.CheckBox();
            this.label88 = new System.Windows.Forms.Label();
            this.comboBox4 = new System.Windows.Forms.ComboBox();
            this.groupBox2.SuspendLayout();
            this.groupBox10.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.GroupBoxControl_ChipSelection.SuspendLayout();
            this.GroupBoxControl_Setting.SuspendLayout();
            this.GroupBoxControl_StimulationConfiguration.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.AccelerationGroup.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.Stimulation.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.GroupBoxControl_NavigationStartStop.SuspendLayout();
            this.GroupBoxControl_StimulationIndicator.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.GroupBoxControl_NavigationButton.SuspendLayout();
            this.GroupBoxControl_NavigationTargets.SuspendLayout();
            this.GroupBoxControl_NavigationParameters.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox17.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.EnableSound);
            this.groupBox2.Controls.Add(this.Gamepad_CheckBox);
            this.groupBox2.Controls.Add(this.groupBox10);
            this.groupBox2.Controls.Add(this.GroupBoxControl_ChipSelection);
            this.groupBox2.Controls.Add(this.GroupBoxControl_Setting);
            this.groupBox2.Controls.Add(this.GroupBoxControl_StimulationConfiguration);
            this.groupBox2.Controls.Add(this.groupBox5);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.Stimulation);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox2.Location = new System.Drawing.Point(9, 3);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox2.Size = new System.Drawing.Size(1749, 865);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Cyborg Insects Fire Watch";
            // 
            // EnableSound
            // 
            this.EnableSound.AutoSize = true;
            this.EnableSound.Enabled = false;
            this.EnableSound.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.EnableSound.Location = new System.Drawing.Point(657, 340);
            this.EnableSound.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.EnableSound.Name = "EnableSound";
            this.EnableSound.Size = new System.Drawing.Size(242, 26);
            this.EnableSound.TabIndex = 138;
            this.EnableSound.Text = "Enable Stimulation Sound";
            this.EnableSound.UseVisualStyleBackColor = true;
            // 
            // Gamepad_CheckBox
            // 
            this.Gamepad_CheckBox.AutoSize = true;
            this.Gamepad_CheckBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Gamepad_CheckBox.Location = new System.Drawing.Point(657, 298);
            this.Gamepad_CheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Gamepad_CheckBox.Name = "Gamepad_CheckBox";
            this.Gamepad_CheckBox.Size = new System.Drawing.Size(175, 26);
            this.Gamepad_CheckBox.TabIndex = 137;
            this.Gamepad_CheckBox.Text = "Enable Gamepad";
            this.Gamepad_CheckBox.UseVisualStyleBackColor = true;
            this.Gamepad_CheckBox.CheckedChanged += new System.EventHandler(this.Gamepad_CheckBox_CheckedChanged);
            // 
            // groupBox10
            // 
            this.groupBox10.Controls.Add(this.label89);
            this.groupBox10.Controls.Add(this.FireWatch_MaxTemp);
            this.groupBox10.Controls.Add(this.ShouldWeStreamImage);
            this.groupBox10.Controls.Add(this.btHMfound_MCU);
            this.groupBox10.Controls.Add(this.label67);
            this.groupBox10.Controls.Add(this.tbTemperaturmin);
            this.groupBox10.Controls.Add(this.label68);
            this.groupBox10.Controls.Add(this.pictureBox1);
            this.groupBox10.Controls.Add(this.tbTemperaturemax);
            this.groupBox10.Location = new System.Drawing.Point(14, 32);
            this.groupBox10.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox10.Size = new System.Drawing.Size(632, 440);
            this.groupBox10.TabIndex = 122;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "IR sensor";
            // 
            // label89
            // 
            this.label89.AutoSize = true;
            this.label89.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label89.Location = new System.Drawing.Point(16, 131);
            this.label89.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label89.Name = "label89";
            this.label89.Size = new System.Drawing.Size(128, 22);
            this.label89.TabIndex = 145;
            this.label89.Text = "Threshold (°C)";
            // 
            // FireWatch_MaxTemp
            // 
            this.FireWatch_MaxTemp.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.FireWatch_MaxTemp.Location = new System.Drawing.Point(159, 126);
            this.FireWatch_MaxTemp.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.FireWatch_MaxTemp.Name = "FireWatch_MaxTemp";
            this.FireWatch_MaxTemp.Size = new System.Drawing.Size(58, 28);
            this.FireWatch_MaxTemp.TabIndex = 144;
            this.FireWatch_MaxTemp.Text = " 120";
            this.FireWatch_MaxTemp.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // ShouldWeStreamImage
            // 
            this.ShouldWeStreamImage.AutoSize = true;
            this.ShouldWeStreamImage.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ShouldWeStreamImage.Location = new System.Drawing.Point(16, 180);
            this.ShouldWeStreamImage.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ShouldWeStreamImage.Name = "ShouldWeStreamImage";
            this.ShouldWeStreamImage.Size = new System.Drawing.Size(171, 26);
            this.ShouldWeStreamImage.TabIndex = 128;
            this.ShouldWeStreamImage.Text = "Stream IR (0x80)";
            this.ShouldWeStreamImage.UseVisualStyleBackColor = true;
            // 
            // btHMfound_MCU
            // 
            this.btHMfound_MCU.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.btHMfound_MCU.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.btHMfound_MCU.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btHMfound_MCU.Location = new System.Drawing.Point(46, 266);
            this.btHMfound_MCU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btHMfound_MCU.Name = "btHMfound_MCU";
            this.btHMfound_MCU.Size = new System.Drawing.Size(112, 65);
            this.btHMfound_MCU.TabIndex = 130;
            this.btHMfound_MCU.Text = "Found";
            this.btHMfound_MCU.UseVisualStyleBackColor = false;
            // 
            // label67
            // 
            this.label67.AutoSize = true;
            this.label67.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label67.Location = new System.Drawing.Point(16, 37);
            this.label67.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label67.Name = "label67";
            this.label67.Size = new System.Drawing.Size(131, 22);
            this.label67.TabIndex = 20;
            this.label67.Text = "Max Temp (°C)";
            // 
            // tbTemperaturmin
            // 
            this.tbTemperaturmin.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbTemperaturmin.Location = new System.Drawing.Point(159, 82);
            this.tbTemperaturmin.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tbTemperaturmin.Name = "tbTemperaturmin";
            this.tbTemperaturmin.Size = new System.Drawing.Size(58, 28);
            this.tbTemperaturmin.TabIndex = 19;
            this.tbTemperaturmin.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label68
            // 
            this.label68.AutoSize = true;
            this.label68.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label68.Location = new System.Drawing.Point(16, 86);
            this.label68.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label68.Name = "label68";
            this.label68.Size = new System.Drawing.Size(126, 22);
            this.label68.TabIndex = 20;
            this.label68.Text = "Min Temp (°C)";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(230, 31);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(383, 393);
            this.pictureBox1.TabIndex = 18;
            this.pictureBox1.TabStop = false;
            // 
            // tbTemperaturemax
            // 
            this.tbTemperaturemax.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbTemperaturemax.Location = new System.Drawing.Point(159, 32);
            this.tbTemperaturemax.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tbTemperaturemax.Name = "tbTemperaturemax";
            this.tbTemperaturemax.Size = new System.Drawing.Size(58, 28);
            this.tbTemperaturemax.TabIndex = 19;
            this.tbTemperaturemax.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // GroupBoxControl_ChipSelection
            // 
            this.GroupBoxControl_ChipSelection.Controls.Add(this.Button_BlueToothConnection);
            this.GroupBoxControl_ChipSelection.Controls.Add(this.cbChipID);
            this.GroupBoxControl_ChipSelection.Controls.Add(this.label59);
            this.GroupBoxControl_ChipSelection.Location = new System.Drawing.Point(14, 500);
            this.GroupBoxControl_ChipSelection.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_ChipSelection.Name = "GroupBoxControl_ChipSelection";
            this.GroupBoxControl_ChipSelection.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_ChipSelection.Size = new System.Drawing.Size(632, 100);
            this.GroupBoxControl_ChipSelection.TabIndex = 30;
            this.GroupBoxControl_ChipSelection.TabStop = false;
            this.GroupBoxControl_ChipSelection.Text = "Chip Select";
            // 
            // Button_BlueToothConnection
            // 
            this.Button_BlueToothConnection.Location = new System.Drawing.Point(340, 42);
            this.Button_BlueToothConnection.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Button_BlueToothConnection.Name = "Button_BlueToothConnection";
            this.Button_BlueToothConnection.Size = new System.Drawing.Size(112, 35);
            this.Button_BlueToothConnection.TabIndex = 2;
            this.Button_BlueToothConnection.Text = "Connect";
            this.Button_BlueToothConnection.UseVisualStyleBackColor = true;
            this.Button_BlueToothConnection.Click += new System.EventHandler(this.Button_BlueToothConnection_Click);
            // 
            // cbChipID
            // 
            this.cbChipID.FormattingEnabled = true;
            this.cbChipID.Location = new System.Drawing.Point(104, 40);
            this.cbChipID.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbChipID.Name = "cbChipID";
            this.cbChipID.Size = new System.Drawing.Size(226, 33);
            this.cbChipID.TabIndex = 1;
            // 
            // label59
            // 
            this.label59.AutoSize = true;
            this.label59.Location = new System.Drawing.Point(14, 45);
            this.label59.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label59.Name = "label59";
            this.label59.Size = new System.Drawing.Size(83, 25);
            this.label59.TabIndex = 0;
            this.label59.Text = "Chip ID:";
            // 
            // GroupBoxControl_Setting
            // 
            this.GroupBoxControl_Setting.Controls.Add(this.TextRequestData);
            this.GroupBoxControl_Setting.Controls.Add(this.label1);
            this.GroupBoxControl_Setting.Controls.Add(this.Button_Serial_OpenPorts);
            this.GroupBoxControl_Setting.Controls.Add(this.LabelBox_Serial_Status);
            this.GroupBoxControl_Setting.Controls.Add(this.label2);
            this.GroupBoxControl_Setting.Controls.Add(this.CheckBox_BlueTooth_AutoLoad);
            this.GroupBoxControl_Setting.Controls.Add(this.TextBox_BatteryVoltage);
            this.GroupBoxControl_Setting.Controls.Add(this.label4);
            this.GroupBoxControl_Setting.Controls.Add(this.CheckBox_Serial_BaudRate);
            this.GroupBoxControl_Setting.Controls.Add(this.CheckBox_SerialPorts);
            this.GroupBoxControl_Setting.Controls.Add(this.tbReceviedData);
            this.GroupBoxControl_Setting.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GroupBoxControl_Setting.Location = new System.Drawing.Point(14, 628);
            this.GroupBoxControl_Setting.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_Setting.Name = "GroupBoxControl_Setting";
            this.GroupBoxControl_Setting.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_Setting.Size = new System.Drawing.Size(633, 220);
            this.GroupBoxControl_Setting.TabIndex = 0;
            this.GroupBoxControl_Setting.TabStop = false;
            this.GroupBoxControl_Setting.Text = "Setting";
            // 
            // TextRequestData
            // 
            this.TextRequestData.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextRequestData.Location = new System.Drawing.Point(492, 68);
            this.TextRequestData.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextRequestData.Name = "TextRequestData";
            this.TextRequestData.ReadOnly = true;
            this.TextRequestData.Size = new System.Drawing.Size(70, 30);
            this.TextRequestData.TabIndex = 42;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(324, 46);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 25);
            this.label1.TabIndex = 11;
            this.label1.Text = "Vbat (V)";
            // 
            // Button_Serial_OpenPorts
            // 
            this.Button_Serial_OpenPorts.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_Serial_OpenPorts.Location = new System.Drawing.Point(3, 32);
            this.Button_Serial_OpenPorts.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Button_Serial_OpenPorts.Name = "Button_Serial_OpenPorts";
            this.Button_Serial_OpenPorts.Size = new System.Drawing.Size(94, 68);
            this.Button_Serial_OpenPorts.TabIndex = 8;
            this.Button_Serial_OpenPorts.Text = "Open";
            this.Button_Serial_OpenPorts.UseVisualStyleBackColor = true;
            this.Button_Serial_OpenPorts.Click += new System.EventHandler(this.Button_Serial_OpenPorts_Click);
            this.Button_Serial_OpenPorts.MouseLeave += new System.EventHandler(this.Button_Serial_OpenPorts_MouseLeave);
            this.Button_Serial_OpenPorts.MouseHover += new System.EventHandler(this.Button_Serial_OpenPorts_MouseHover);
            // 
            // LabelBox_Serial_Status
            // 
            this.LabelBox_Serial_Status.AutoSize = true;
            this.LabelBox_Serial_Status.BackColor = System.Drawing.SystemColors.Control;
            this.LabelBox_Serial_Status.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LabelBox_Serial_Status.Location = new System.Drawing.Point(15, 222);
            this.LabelBox_Serial_Status.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LabelBox_Serial_Status.Name = "LabelBox_Serial_Status";
            this.LabelBox_Serial_Status.Size = new System.Drawing.Size(68, 25);
            this.LabelBox_Serial_Status.TabIndex = 0;
            this.LabelBox_Serial_Status.Text = "Status";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(105, 74);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(83, 22);
            this.label2.TabIndex = 1;
            this.label2.Text = "Baudrate";
            // 
            // CheckBox_BlueTooth_AutoLoad
            // 
            this.CheckBox_BlueTooth_AutoLoad.AutoSize = true;
            this.CheckBox_BlueTooth_AutoLoad.Location = new System.Drawing.Point(495, 26);
            this.CheckBox_BlueTooth_AutoLoad.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckBox_BlueTooth_AutoLoad.Name = "CheckBox_BlueTooth_AutoLoad";
            this.CheckBox_BlueTooth_AutoLoad.Size = new System.Drawing.Size(121, 29);
            this.CheckBox_BlueTooth_AutoLoad.TabIndex = 10;
            this.CheckBox_BlueTooth_AutoLoad.Text = "Auto load";
            this.CheckBox_BlueTooth_AutoLoad.UseVisualStyleBackColor = true;
            this.CheckBox_BlueTooth_AutoLoad.CheckedChanged += new System.EventHandler(this.CheckBox_BlueTooth_AutoLoad_CheckedChanged);
            // 
            // TextBox_BatteryVoltage
            // 
            this.TextBox_BatteryVoltage.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBox_BatteryVoltage.Location = new System.Drawing.Point(416, 42);
            this.TextBox_BatteryVoltage.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBox_BatteryVoltage.Name = "TextBox_BatteryVoltage";
            this.TextBox_BatteryVoltage.ReadOnly = true;
            this.TextBox_BatteryVoltage.Size = new System.Drawing.Size(58, 30);
            this.TextBox_BatteryVoltage.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(105, 28);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(89, 22);
            this.label4.TabIndex = 1;
            this.label4.Text = "COM Port";
            // 
            // CheckBox_Serial_BaudRate
            // 
            this.CheckBox_Serial_BaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CheckBox_Serial_BaudRate.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CheckBox_Serial_BaudRate.FormattingEnabled = true;
            this.CheckBox_Serial_BaudRate.Items.AddRange(new object[] {
            "9600",
            "19200",
            "38400",
            "57600",
            "115200",
            "230400",
            "460800",
            "921600",
            "1843200"});
            this.CheckBox_Serial_BaudRate.Location = new System.Drawing.Point(202, 66);
            this.CheckBox_Serial_BaudRate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckBox_Serial_BaudRate.Name = "CheckBox_Serial_BaudRate";
            this.CheckBox_Serial_BaudRate.Size = new System.Drawing.Size(102, 33);
            this.CheckBox_Serial_BaudRate.TabIndex = 0;
            this.CheckBox_Serial_BaudRate.SelectedIndexChanged += new System.EventHandler(this.CheckBox_Serial_BaudRate_SelectedIndexChanged);
            // 
            // CheckBox_SerialPorts
            // 
            this.CheckBox_SerialPorts.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.CheckBox_SerialPorts.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CheckBox_SerialPorts.FormattingEnabled = true;
            this.CheckBox_SerialPorts.Location = new System.Drawing.Point(202, 20);
            this.CheckBox_SerialPorts.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckBox_SerialPorts.Name = "CheckBox_SerialPorts";
            this.CheckBox_SerialPorts.Size = new System.Drawing.Size(102, 33);
            this.CheckBox_SerialPorts.TabIndex = 0;
            this.CheckBox_SerialPorts.SelectedIndexChanged += new System.EventHandler(this.CheckBox_SerialPorts_SelectedIndexChanged);
            this.CheckBox_SerialPorts.Click += new System.EventHandler(this.CheckBox_SerialPorts_Click);
            // 
            // tbReceviedData
            // 
            this.tbReceviedData.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.5F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tbReceviedData.Location = new System.Drawing.Point(16, 112);
            this.tbReceviedData.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tbReceviedData.Multiline = true;
            this.tbReceviedData.Name = "tbReceviedData";
            this.tbReceviedData.ReadOnly = true;
            this.tbReceviedData.Size = new System.Drawing.Size(588, 90);
            this.tbReceviedData.TabIndex = 9;
            // 
            // GroupBoxControl_StimulationConfiguration
            // 
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.cbRightPin);
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.cbLeftPin);
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.cbCercusRight);
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.cbCercusLeft);
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.pictureBox2);
            this.GroupBoxControl_StimulationConfiguration.Controls.Add(this.AccelerationGroup);
            this.GroupBoxControl_StimulationConfiguration.Location = new System.Drawing.Point(1080, 32);
            this.GroupBoxControl_StimulationConfiguration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_StimulationConfiguration.Name = "GroupBoxControl_StimulationConfiguration";
            this.GroupBoxControl_StimulationConfiguration.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_StimulationConfiguration.Size = new System.Drawing.Size(654, 343);
            this.GroupBoxControl_StimulationConfiguration.TabIndex = 2;
            this.GroupBoxControl_StimulationConfiguration.TabStop = false;
            this.GroupBoxControl_StimulationConfiguration.Text = "Stimulation Configuration";
            // 
            // cbRightPin
            // 
            this.cbRightPin.Cursor = System.Windows.Forms.Cursors.No;
            this.cbRightPin.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbRightPin.FormattingEnabled = true;
            this.cbRightPin.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.cbRightPin.Location = new System.Drawing.Point(194, 183);
            this.cbRightPin.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbRightPin.Name = "cbRightPin";
            this.cbRightPin.Size = new System.Drawing.Size(91, 30);
            this.cbRightPin.TabIndex = 97;
            // 
            // cbLeftPin
            // 
            this.cbLeftPin.Cursor = System.Windows.Forms.Cursors.No;
            this.cbLeftPin.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbLeftPin.FormattingEnabled = true;
            this.cbLeftPin.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.cbLeftPin.Location = new System.Drawing.Point(56, 183);
            this.cbLeftPin.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbLeftPin.Name = "cbLeftPin";
            this.cbLeftPin.Size = new System.Drawing.Size(84, 30);
            this.cbLeftPin.TabIndex = 98;
            // 
            // cbCercusRight
            // 
            this.cbCercusRight.Cursor = System.Windows.Forms.Cursors.No;
            this.cbCercusRight.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbCercusRight.FormattingEnabled = true;
            this.cbCercusRight.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.cbCercusRight.Location = new System.Drawing.Point(194, 275);
            this.cbCercusRight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbCercusRight.Name = "cbCercusRight";
            this.cbCercusRight.Size = new System.Drawing.Size(84, 30);
            this.cbCercusRight.TabIndex = 100;
            // 
            // cbCercusLeft
            // 
            this.cbCercusLeft.Cursor = System.Windows.Forms.Cursors.No;
            this.cbCercusLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbCercusLeft.FormattingEnabled = true;
            this.cbCercusLeft.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.cbCercusLeft.Location = new System.Drawing.Point(57, 275);
            this.cbCercusLeft.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbCercusLeft.Name = "cbCercusLeft";
            this.cbCercusLeft.Size = new System.Drawing.Size(82, 30);
            this.cbCercusLeft.TabIndex = 99;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(14, 26);
            this.pictureBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(290, 300);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 108;
            this.pictureBox2.TabStop = false;
            // 
            // AccelerationGroup
            // 
            this.AccelerationGroup.Controls.Add(this.label64);
            this.AccelerationGroup.Controls.Add(this.label62);
            this.AccelerationGroup.Controls.Add(this.GoFoward_Postion1);
            this.AccelerationGroup.Controls.Add(this.GoFoward_Postion2);
            this.AccelerationGroup.Location = new System.Drawing.Point(321, 17);
            this.AccelerationGroup.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AccelerationGroup.Name = "AccelerationGroup";
            this.AccelerationGroup.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AccelerationGroup.Size = new System.Drawing.Size(322, 137);
            this.AccelerationGroup.TabIndex = 110;
            this.AccelerationGroup.TabStop = false;
            this.AccelerationGroup.Text = "Acceleration";
            // 
            // label64
            // 
            this.label64.AutoSize = true;
            this.label64.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label64.Location = new System.Drawing.Point(172, 35);
            this.label64.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label64.Name = "label64";
            this.label64.Size = new System.Drawing.Size(89, 22);
            this.label64.TabIndex = 13;
            this.label64.Text = "Position 2";
            // 
            // label62
            // 
            this.label62.AutoSize = true;
            this.label62.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label62.Location = new System.Drawing.Point(38, 35);
            this.label62.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label62.Name = "label62";
            this.label62.Size = new System.Drawing.Size(89, 22);
            this.label62.TabIndex = 12;
            this.label62.Text = "Position 1";
            // 
            // GoFoward_Postion1
            // 
            this.GoFoward_Postion1.FormattingEnabled = true;
            this.GoFoward_Postion1.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.GoFoward_Postion1.Location = new System.Drawing.Point(39, 71);
            this.GoFoward_Postion1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoFoward_Postion1.Name = "GoFoward_Postion1";
            this.GoFoward_Postion1.Size = new System.Drawing.Size(84, 33);
            this.GoFoward_Postion1.TabIndex = 9;
            // 
            // GoFoward_Postion2
            // 
            this.GoFoward_Postion2.FormattingEnabled = true;
            this.GoFoward_Postion2.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.GoFoward_Postion2.Location = new System.Drawing.Point(176, 71);
            this.GoFoward_Postion2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoFoward_Postion2.Name = "GoFoward_Postion2";
            this.GoFoward_Postion2.Size = new System.Drawing.Size(91, 33);
            this.GoFoward_Postion2.TabIndex = 8;
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label57);
            this.groupBox5.Controls.Add(this.TurnToLeft_V2);
            this.groupBox5.Controls.Add(this.label54);
            this.groupBox5.Controls.Add(this.TurnToLeft_V1);
            this.groupBox5.Controls.Add(this.TurnToLeft_Period);
            this.groupBox5.Controls.Add(this.label38);
            this.groupBox5.Controls.Add(this.label39);
            this.groupBox5.Controls.Add(this.label40);
            this.groupBox5.Controls.Add(this.label41);
            this.groupBox5.Controls.Add(this.label42);
            this.groupBox5.Controls.Add(this.label43);
            this.groupBox5.Controls.Add(this.label44);
            this.groupBox5.Controls.Add(this.TurnToLeft_Amplitude);
            this.groupBox5.Controls.Add(this.TurnToLeft_Toff2);
            this.groupBox5.Controls.Add(this.TurnToLeft_Toff1);
            this.groupBox5.Controls.Add(this.TurnToLeft_Ton2);
            this.groupBox5.Controls.Add(this.TurnToLeft_Ton1);
            this.groupBox5.Controls.Add(this.TurnToLeft_Duration);
            this.groupBox5.Controls.Add(this.Enable_TurnToLeft);
            this.groupBox5.Location = new System.Drawing.Point(858, 394);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox5.Size = new System.Drawing.Size(272, 454);
            this.groupBox5.TabIndex = 102;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Turn Left";
            // 
            // label57
            // 
            this.label57.AutoSize = true;
            this.label57.Location = new System.Drawing.Point(9, 395);
            this.label57.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label57.Name = "label57";
            this.label57.Size = new System.Drawing.Size(134, 25);
            this.label57.TabIndex = 7;
            this.label57.Text = "Voltage 2 (V):";
            // 
            // TurnToLeft_V2
            // 
            this.TurnToLeft_V2.Location = new System.Drawing.Point(158, 392);
            this.TurnToLeft_V2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_V2.Name = "TurnToLeft_V2";
            this.TurnToLeft_V2.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_V2.TabIndex = 6;
            this.TurnToLeft_V2.Leave += new System.EventHandler(this.TurnToLeft_V2_Leave);
            // 
            // label54
            // 
            this.label54.AutoSize = true;
            this.label54.Location = new System.Drawing.Point(9, 352);
            this.label54.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label54.Name = "label54";
            this.label54.Size = new System.Drawing.Size(134, 25);
            this.label54.TabIndex = 5;
            this.label54.Text = "Voltage 1 (V):";
            // 
            // TurnToLeft_V1
            // 
            this.TurnToLeft_V1.Location = new System.Drawing.Point(158, 351);
            this.TurnToLeft_V1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_V1.Name = "TurnToLeft_V1";
            this.TurnToLeft_V1.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_V1.TabIndex = 4;
            this.TurnToLeft_V1.Leave += new System.EventHandler(this.TurnToLeft_V1_Leave);
            // 
            // TurnToLeft_Period
            // 
            this.TurnToLeft_Period.Location = new System.Drawing.Point(158, 102);
            this.TurnToLeft_Period.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Period.Name = "TurnToLeft_Period";
            this.TurnToLeft_Period.ReadOnly = true;
            this.TurnToLeft_Period.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Period.TabIndex = 2;
            // 
            // label38
            // 
            this.label38.AutoSize = true;
            this.label38.Location = new System.Drawing.Point(9, 309);
            this.label38.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label38.Name = "label38";
            this.label38.Size = new System.Drawing.Size(138, 25);
            this.label38.TabIndex = 3;
            this.label38.Text = "Amplitude (V):";
            // 
            // label39
            // 
            this.label39.AutoSize = true;
            this.label39.Location = new System.Drawing.Point(9, 271);
            this.label39.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label39.Name = "label39";
            this.label39.Size = new System.Drawing.Size(109, 25);
            this.label39.TabIndex = 3;
            this.label39.Text = "Off Time 2:";
            // 
            // label40
            // 
            this.label40.AutoSize = true;
            this.label40.Location = new System.Drawing.Point(9, 226);
            this.label40.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label40.Name = "label40";
            this.label40.Size = new System.Drawing.Size(109, 25);
            this.label40.TabIndex = 3;
            this.label40.Text = "Off Time 1:";
            // 
            // label41
            // 
            this.label41.AutoSize = true;
            this.label41.Location = new System.Drawing.Point(9, 185);
            this.label41.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label41.Name = "label41";
            this.label41.Size = new System.Drawing.Size(110, 25);
            this.label41.TabIndex = 3;
            this.label41.Text = "On Time 2:";
            // 
            // label42
            // 
            this.label42.AutoSize = true;
            this.label42.Location = new System.Drawing.Point(9, 145);
            this.label42.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label42.Name = "label42";
            this.label42.Size = new System.Drawing.Size(110, 25);
            this.label42.TabIndex = 3;
            this.label42.Text = "On Time 1:";
            // 
            // label43
            // 
            this.label43.AutoSize = true;
            this.label43.Location = new System.Drawing.Point(9, 105);
            this.label43.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label43.Name = "label43";
            this.label43.Size = new System.Drawing.Size(154, 25);
            this.label43.TabIndex = 3;
            this.label43.Text = "Frequency (Hz):";
            // 
            // label44
            // 
            this.label44.AutoSize = true;
            this.label44.Location = new System.Drawing.Point(9, 65);
            this.label44.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label44.Name = "label44";
            this.label44.Size = new System.Drawing.Size(136, 25);
            this.label44.TabIndex = 3;
            this.label44.Text = "Duration (ms):";
            // 
            // TurnToLeft_Amplitude
            // 
            this.TurnToLeft_Amplitude.Location = new System.Drawing.Point(158, 309);
            this.TurnToLeft_Amplitude.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Amplitude.Name = "TurnToLeft_Amplitude";
            this.TurnToLeft_Amplitude.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Amplitude.TabIndex = 2;
            this.TurnToLeft_Amplitude.Leave += new System.EventHandler(this.TurnToLeft_Amplitude_Leave);
            // 
            // TurnToLeft_Toff2
            // 
            this.TurnToLeft_Toff2.Location = new System.Drawing.Point(158, 268);
            this.TurnToLeft_Toff2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Toff2.Name = "TurnToLeft_Toff2";
            this.TurnToLeft_Toff2.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Toff2.TabIndex = 2;
            this.TurnToLeft_Toff2.TextChanged += new System.EventHandler(this.TurnToLeft_Toff2_TextChanged);
            // 
            // TurnToLeft_Toff1
            // 
            this.TurnToLeft_Toff1.Location = new System.Drawing.Point(158, 226);
            this.TurnToLeft_Toff1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Toff1.Name = "TurnToLeft_Toff1";
            this.TurnToLeft_Toff1.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Toff1.TabIndex = 2;
            this.TurnToLeft_Toff1.TextChanged += new System.EventHandler(this.TurnToLeft_Toff1_TextChanged);
            // 
            // TurnToLeft_Ton2
            // 
            this.TurnToLeft_Ton2.Location = new System.Drawing.Point(158, 185);
            this.TurnToLeft_Ton2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Ton2.Name = "TurnToLeft_Ton2";
            this.TurnToLeft_Ton2.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Ton2.TabIndex = 2;
            this.TurnToLeft_Ton2.TextChanged += new System.EventHandler(this.TurnToLeft_Ton2_TextChanged);
            // 
            // TurnToLeft_Ton1
            // 
            this.TurnToLeft_Ton1.Location = new System.Drawing.Point(158, 143);
            this.TurnToLeft_Ton1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Ton1.Name = "TurnToLeft_Ton1";
            this.TurnToLeft_Ton1.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Ton1.TabIndex = 2;
            this.TurnToLeft_Ton1.TextChanged += new System.EventHandler(this.TurnToLeft_Ton1_TextChanged);
            // 
            // TurnToLeft_Duration
            // 
            this.TurnToLeft_Duration.Location = new System.Drawing.Point(158, 60);
            this.TurnToLeft_Duration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToLeft_Duration.Name = "TurnToLeft_Duration";
            this.TurnToLeft_Duration.Size = new System.Drawing.Size(98, 30);
            this.TurnToLeft_Duration.TabIndex = 2;
            this.TurnToLeft_Duration.TextChanged += new System.EventHandler(this.TurnToLeft_Duration_TextChanged);
            // 
            // Enable_TurnToLeft
            // 
            this.Enable_TurnToLeft.AutoSize = true;
            this.Enable_TurnToLeft.Location = new System.Drawing.Point(9, 29);
            this.Enable_TurnToLeft.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Enable_TurnToLeft.Name = "Enable_TurnToLeft";
            this.Enable_TurnToLeft.Size = new System.Drawing.Size(170, 29);
            this.Enable_TurnToLeft.TabIndex = 1;
            this.Enable_TurnToLeft.Text = "Enable/Disable";
            this.Enable_TurnToLeft.UseVisualStyleBackColor = true;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label60);
            this.groupBox3.Controls.Add(this.TurnToRight_V2);
            this.groupBox3.Controls.Add(this.label56);
            this.groupBox3.Controls.Add(this.TurnToRight_V1);
            this.groupBox3.Controls.Add(this.TurnToRight_Period);
            this.groupBox3.Controls.Add(this.label30);
            this.groupBox3.Controls.Add(this.label29);
            this.groupBox3.Controls.Add(this.label28);
            this.groupBox3.Controls.Add(this.label27);
            this.groupBox3.Controls.Add(this.label26);
            this.groupBox3.Controls.Add(this.label24);
            this.groupBox3.Controls.Add(this.TurnToRight_Amplitude);
            this.groupBox3.Controls.Add(this.TurnToRight_Toff2);
            this.groupBox3.Controls.Add(this.TurnToRight_Toff1);
            this.groupBox3.Controls.Add(this.TurnToRight_Ton2);
            this.groupBox3.Controls.Add(this.TurnToRight_Ton1);
            this.groupBox3.Controls.Add(this.TurnToRight_Duration);
            this.groupBox3.Controls.Add(this.Enable_TurnToRight);
            this.groupBox3.Controls.Add(this.label25);
            this.groupBox3.Location = new System.Drawing.Point(1461, 394);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox3.Size = new System.Drawing.Size(272, 454);
            this.groupBox3.TabIndex = 104;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Turn Right";
            // 
            // label60
            // 
            this.label60.AutoSize = true;
            this.label60.Location = new System.Drawing.Point(9, 397);
            this.label60.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label60.Name = "label60";
            this.label60.Size = new System.Drawing.Size(134, 25);
            this.label60.TabIndex = 11;
            this.label60.Text = "Voltage 2 (V):";
            // 
            // TurnToRight_V2
            // 
            this.TurnToRight_V2.Location = new System.Drawing.Point(162, 392);
            this.TurnToRight_V2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_V2.Name = "TurnToRight_V2";
            this.TurnToRight_V2.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_V2.TabIndex = 10;
            this.TurnToRight_V2.Leave += new System.EventHandler(this.TurnToRight_V2_Leave);
            // 
            // label56
            // 
            this.label56.AutoSize = true;
            this.label56.Location = new System.Drawing.Point(9, 355);
            this.label56.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label56.Name = "label56";
            this.label56.Size = new System.Drawing.Size(134, 25);
            this.label56.TabIndex = 9;
            this.label56.Text = "Voltage 1 (V):";
            // 
            // TurnToRight_V1
            // 
            this.TurnToRight_V1.Location = new System.Drawing.Point(162, 351);
            this.TurnToRight_V1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_V1.Name = "TurnToRight_V1";
            this.TurnToRight_V1.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_V1.TabIndex = 8;
            this.TurnToRight_V1.Leave += new System.EventHandler(this.TurnToRight_V1_Leave);
            // 
            // TurnToRight_Period
            // 
            this.TurnToRight_Period.Location = new System.Drawing.Point(162, 102);
            this.TurnToRight_Period.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Period.Name = "TurnToRight_Period";
            this.TurnToRight_Period.ReadOnly = true;
            this.TurnToRight_Period.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Period.TabIndex = 2;
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(9, 314);
            this.label30.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(138, 25);
            this.label30.TabIndex = 3;
            this.label30.Text = "Amplitude (V):";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(9, 272);
            this.label29.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(109, 25);
            this.label29.TabIndex = 3;
            this.label29.Text = "Off Time 2:";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(9, 231);
            this.label28.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(109, 25);
            this.label28.TabIndex = 3;
            this.label28.Text = "Off Time 1:";
            // 
            // label27
            // 
            this.label27.AutoSize = true;
            this.label27.Location = new System.Drawing.Point(9, 189);
            this.label27.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label27.Name = "label27";
            this.label27.Size = new System.Drawing.Size(110, 25);
            this.label27.TabIndex = 3;
            this.label27.Text = "On Time 2:";
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(9, 148);
            this.label26.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(110, 25);
            this.label26.TabIndex = 3;
            this.label26.Text = "On Time 1:";
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(9, 65);
            this.label24.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(136, 25);
            this.label24.TabIndex = 3;
            this.label24.Text = "Duration (ms):";
            // 
            // TurnToRight_Amplitude
            // 
            this.TurnToRight_Amplitude.Location = new System.Drawing.Point(162, 309);
            this.TurnToRight_Amplitude.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Amplitude.Name = "TurnToRight_Amplitude";
            this.TurnToRight_Amplitude.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Amplitude.TabIndex = 2;
            this.TurnToRight_Amplitude.Leave += new System.EventHandler(this.TurnToRight_Amplitude_Leave);
            // 
            // TurnToRight_Toff2
            // 
            this.TurnToRight_Toff2.Location = new System.Drawing.Point(162, 268);
            this.TurnToRight_Toff2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Toff2.Name = "TurnToRight_Toff2";
            this.TurnToRight_Toff2.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Toff2.TabIndex = 2;
            this.TurnToRight_Toff2.TextChanged += new System.EventHandler(this.TurnToRight_Toff2_TextChanged);
            // 
            // TurnToRight_Toff1
            // 
            this.TurnToRight_Toff1.Location = new System.Drawing.Point(162, 226);
            this.TurnToRight_Toff1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Toff1.Name = "TurnToRight_Toff1";
            this.TurnToRight_Toff1.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Toff1.TabIndex = 2;
            this.TurnToRight_Toff1.TextChanged += new System.EventHandler(this.TurnToRight_Toff1_TextChanged);
            // 
            // TurnToRight_Ton2
            // 
            this.TurnToRight_Ton2.Location = new System.Drawing.Point(162, 185);
            this.TurnToRight_Ton2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Ton2.Name = "TurnToRight_Ton2";
            this.TurnToRight_Ton2.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Ton2.TabIndex = 2;
            this.TurnToRight_Ton2.TextChanged += new System.EventHandler(this.TurnToRight_Ton2_TextChanged);
            // 
            // TurnToRight_Ton1
            // 
            this.TurnToRight_Ton1.Location = new System.Drawing.Point(162, 143);
            this.TurnToRight_Ton1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Ton1.Name = "TurnToRight_Ton1";
            this.TurnToRight_Ton1.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Ton1.TabIndex = 2;
            this.TurnToRight_Ton1.TextChanged += new System.EventHandler(this.TurnToRight_Ton1_TextChanged);
            // 
            // TurnToRight_Duration
            // 
            this.TurnToRight_Duration.Location = new System.Drawing.Point(162, 60);
            this.TurnToRight_Duration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TurnToRight_Duration.Name = "TurnToRight_Duration";
            this.TurnToRight_Duration.Size = new System.Drawing.Size(98, 30);
            this.TurnToRight_Duration.TabIndex = 2;
            this.TurnToRight_Duration.TextChanged += new System.EventHandler(this.TurnToRight_Duration_TextChanged);
            // 
            // Enable_TurnToRight
            // 
            this.Enable_TurnToRight.AutoSize = true;
            this.Enable_TurnToRight.Location = new System.Drawing.Point(9, 29);
            this.Enable_TurnToRight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Enable_TurnToRight.Name = "Enable_TurnToRight";
            this.Enable_TurnToRight.Size = new System.Drawing.Size(170, 29);
            this.Enable_TurnToRight.TabIndex = 1;
            this.Enable_TurnToRight.Text = "Enable/Disable";
            this.Enable_TurnToRight.UseVisualStyleBackColor = true;
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(9, 106);
            this.label25.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(154, 25);
            this.label25.TabIndex = 3;
            this.label25.Text = "Frequency (Hz):";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label58);
            this.groupBox4.Controls.Add(this.GoForward_V2);
            this.groupBox4.Controls.Add(this.label55);
            this.groupBox4.Controls.Add(this.GoForward_V1);
            this.groupBox4.Controls.Add(this.GoForward_Period);
            this.groupBox4.Controls.Add(this.label31);
            this.groupBox4.Controls.Add(this.label32);
            this.groupBox4.Controls.Add(this.label33);
            this.groupBox4.Controls.Add(this.label34);
            this.groupBox4.Controls.Add(this.label35);
            this.groupBox4.Controls.Add(this.label36);
            this.groupBox4.Controls.Add(this.label37);
            this.groupBox4.Controls.Add(this.GoForward_Amplitude);
            this.groupBox4.Controls.Add(this.GoForward_Toff2);
            this.groupBox4.Controls.Add(this.GoForward_Toff1);
            this.groupBox4.Controls.Add(this.GoForward_Ton2);
            this.groupBox4.Controls.Add(this.GoForward_Ton1);
            this.groupBox4.Controls.Add(this.GoForward_Duration);
            this.groupBox4.Controls.Add(this.Enable_Forward);
            this.groupBox4.Location = new System.Drawing.Point(1160, 394);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox4.Size = new System.Drawing.Size(272, 454);
            this.groupBox4.TabIndex = 103;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Accelerate";
            // 
            // label58
            // 
            this.label58.AutoSize = true;
            this.label58.Location = new System.Drawing.Point(8, 397);
            this.label58.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label58.Name = "label58";
            this.label58.Size = new System.Drawing.Size(134, 25);
            this.label58.TabIndex = 9;
            this.label58.Text = "Voltage 2 (V):";
            // 
            // GoForward_V2
            // 
            this.GoForward_V2.Location = new System.Drawing.Point(154, 392);
            this.GoForward_V2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_V2.Name = "GoForward_V2";
            this.GoForward_V2.Size = new System.Drawing.Size(98, 30);
            this.GoForward_V2.TabIndex = 8;
            this.GoForward_V2.Leave += new System.EventHandler(this.GoForward_V2_Leave);
            // 
            // label55
            // 
            this.label55.AutoSize = true;
            this.label55.Location = new System.Drawing.Point(8, 355);
            this.label55.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label55.Name = "label55";
            this.label55.Size = new System.Drawing.Size(134, 25);
            this.label55.TabIndex = 7;
            this.label55.Text = "Voltage 1 (V):";
            // 
            // GoForward_V1
            // 
            this.GoForward_V1.Location = new System.Drawing.Point(154, 351);
            this.GoForward_V1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_V1.Name = "GoForward_V1";
            this.GoForward_V1.Size = new System.Drawing.Size(98, 30);
            this.GoForward_V1.TabIndex = 6;
            this.GoForward_V1.Leave += new System.EventHandler(this.GoForward_V1_Leave);
            // 
            // GoForward_Period
            // 
            this.GoForward_Period.Location = new System.Drawing.Point(154, 102);
            this.GoForward_Period.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Period.Name = "GoForward_Period";
            this.GoForward_Period.ReadOnly = true;
            this.GoForward_Period.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Period.TabIndex = 2;
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(8, 314);
            this.label31.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(138, 25);
            this.label31.TabIndex = 3;
            this.label31.Text = "Amplitude (V):";
            // 
            // label32
            // 
            this.label32.AutoSize = true;
            this.label32.Location = new System.Drawing.Point(8, 272);
            this.label32.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label32.Name = "label32";
            this.label32.Size = new System.Drawing.Size(109, 25);
            this.label32.TabIndex = 3;
            this.label32.Text = "Off Time 2:";
            // 
            // label33
            // 
            this.label33.AutoSize = true;
            this.label33.Location = new System.Drawing.Point(8, 231);
            this.label33.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label33.Name = "label33";
            this.label33.Size = new System.Drawing.Size(109, 25);
            this.label33.TabIndex = 3;
            this.label33.Text = "Off Time 1:";
            // 
            // label34
            // 
            this.label34.AutoSize = true;
            this.label34.Location = new System.Drawing.Point(8, 189);
            this.label34.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label34.Name = "label34";
            this.label34.Size = new System.Drawing.Size(110, 25);
            this.label34.TabIndex = 3;
            this.label34.Text = "On Time 2:";
            // 
            // label35
            // 
            this.label35.AutoSize = true;
            this.label35.Location = new System.Drawing.Point(8, 148);
            this.label35.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label35.Name = "label35";
            this.label35.Size = new System.Drawing.Size(110, 25);
            this.label35.TabIndex = 3;
            this.label35.Text = "On Time 1:";
            // 
            // label36
            // 
            this.label36.AutoSize = true;
            this.label36.Location = new System.Drawing.Point(8, 106);
            this.label36.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label36.Name = "label36";
            this.label36.Size = new System.Drawing.Size(154, 25);
            this.label36.TabIndex = 3;
            this.label36.Text = "Frequency (Hz):";
            // 
            // label37
            // 
            this.label37.AutoSize = true;
            this.label37.Location = new System.Drawing.Point(8, 65);
            this.label37.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label37.Name = "label37";
            this.label37.Size = new System.Drawing.Size(136, 25);
            this.label37.TabIndex = 3;
            this.label37.Text = "Duration (ms):";
            // 
            // GoForward_Amplitude
            // 
            this.GoForward_Amplitude.Location = new System.Drawing.Point(154, 309);
            this.GoForward_Amplitude.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Amplitude.Name = "GoForward_Amplitude";
            this.GoForward_Amplitude.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Amplitude.TabIndex = 2;
            this.GoForward_Amplitude.Leave += new System.EventHandler(this.GoForward_Amplitude_Leave);
            // 
            // GoForward_Toff2
            // 
            this.GoForward_Toff2.Location = new System.Drawing.Point(154, 268);
            this.GoForward_Toff2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Toff2.Name = "GoForward_Toff2";
            this.GoForward_Toff2.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Toff2.TabIndex = 2;
            this.GoForward_Toff2.TextChanged += new System.EventHandler(this.GoForward_Toff2_TextChanged);
            // 
            // GoForward_Toff1
            // 
            this.GoForward_Toff1.Location = new System.Drawing.Point(154, 226);
            this.GoForward_Toff1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Toff1.Name = "GoForward_Toff1";
            this.GoForward_Toff1.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Toff1.TabIndex = 2;
            this.GoForward_Toff1.TextChanged += new System.EventHandler(this.GoForward_Toff1_TextChanged);
            // 
            // GoForward_Ton2
            // 
            this.GoForward_Ton2.Location = new System.Drawing.Point(154, 185);
            this.GoForward_Ton2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Ton2.Name = "GoForward_Ton2";
            this.GoForward_Ton2.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Ton2.TabIndex = 2;
            this.GoForward_Ton2.TextChanged += new System.EventHandler(this.GoForward_Ton2_TextChanged);
            // 
            // GoForward_Ton1
            // 
            this.GoForward_Ton1.Location = new System.Drawing.Point(154, 143);
            this.GoForward_Ton1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Ton1.Name = "GoForward_Ton1";
            this.GoForward_Ton1.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Ton1.TabIndex = 2;
            this.GoForward_Ton1.TextChanged += new System.EventHandler(this.GoForward_Ton1_TextChanged);
            // 
            // GoForward_Duration
            // 
            this.GoForward_Duration.Location = new System.Drawing.Point(154, 60);
            this.GoForward_Duration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GoForward_Duration.Name = "GoForward_Duration";
            this.GoForward_Duration.Size = new System.Drawing.Size(98, 30);
            this.GoForward_Duration.TabIndex = 2;
            this.GoForward_Duration.TextChanged += new System.EventHandler(this.GoForward_Duration_TextChanged);
            // 
            // Enable_Forward
            // 
            this.Enable_Forward.AutoSize = true;
            this.Enable_Forward.Location = new System.Drawing.Point(9, 29);
            this.Enable_Forward.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Enable_Forward.Name = "Enable_Forward";
            this.Enable_Forward.Size = new System.Drawing.Size(170, 29);
            this.Enable_Forward.TabIndex = 1;
            this.Enable_Forward.Text = "Enable/Disable";
            this.Enable_Forward.UseVisualStyleBackColor = true;
            // 
            // Stimulation
            // 
            this.Stimulation.Controls.Add(this.label63);
            this.Stimulation.Controls.Add(this.bt_Stimulation_Right);
            this.Stimulation.Controls.Add(this.bt_Stimulation_Forward);
            this.Stimulation.Controls.Add(this.label61);
            this.Stimulation.Controls.Add(this.bt_Stimulation_Stop);
            this.Stimulation.Controls.Add(this.bt_Stimulation_Left);
            this.Stimulation.Location = new System.Drawing.Point(657, 32);
            this.Stimulation.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Stimulation.Name = "Stimulation";
            this.Stimulation.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Stimulation.Size = new System.Drawing.Size(412, 254);
            this.Stimulation.TabIndex = 101;
            this.Stimulation.TabStop = false;
            this.Stimulation.Text = "Stimulation Control";
            // 
            // label63
            // 
            this.label63.AutoSize = true;
            this.label63.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label63.Location = new System.Drawing.Point(9, 448);
            this.label63.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label63.Name = "label63";
            this.label63.Size = new System.Drawing.Size(83, 25);
            this.label63.TabIndex = 4;
            this.label63.Text = "Forward";
            // 
            // bt_Stimulation_Right
            // 
            this.bt_Stimulation_Right.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Stimulation_Right.Location = new System.Drawing.Point(286, 102);
            this.bt_Stimulation_Right.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bt_Stimulation_Right.Name = "bt_Stimulation_Right";
            this.bt_Stimulation_Right.Size = new System.Drawing.Size(117, 63);
            this.bt_Stimulation_Right.TabIndex = 5;
            this.bt_Stimulation_Right.Text = "Right";
            this.bt_Stimulation_Right.UseVisualStyleBackColor = true;
            this.bt_Stimulation_Right.Click += new System.EventHandler(this.bt_Stimulation_Right_Click);
            // 
            // bt_Stimulation_Forward
            // 
            this.bt_Stimulation_Forward.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Stimulation_Forward.Location = new System.Drawing.Point(147, 35);
            this.bt_Stimulation_Forward.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bt_Stimulation_Forward.Name = "bt_Stimulation_Forward";
            this.bt_Stimulation_Forward.Size = new System.Drawing.Size(132, 63);
            this.bt_Stimulation_Forward.TabIndex = 5;
            this.bt_Stimulation_Forward.Text = "Accelerate";
            this.bt_Stimulation_Forward.UseVisualStyleBackColor = true;
            this.bt_Stimulation_Forward.Click += new System.EventHandler(this.bt_Stimulation_Forward_Click);
            // 
            // label61
            // 
            this.label61.AutoSize = true;
            this.label61.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label61.Location = new System.Drawing.Point(-147, 331);
            this.label61.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label61.Name = "label61";
            this.label61.Size = new System.Drawing.Size(102, 25);
            this.label61.TabIndex = 4;
            this.label61.Text = "Turn Right";
            // 
            // bt_Stimulation_Stop
            // 
            this.bt_Stimulation_Stop.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Stimulation_Stop.Location = new System.Drawing.Point(147, 168);
            this.bt_Stimulation_Stop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bt_Stimulation_Stop.Name = "bt_Stimulation_Stop";
            this.bt_Stimulation_Stop.Size = new System.Drawing.Size(132, 63);
            this.bt_Stimulation_Stop.TabIndex = 0;
            this.bt_Stimulation_Stop.Text = "Stop Stimulation";
            this.bt_Stimulation_Stop.UseVisualStyleBackColor = true;
            this.bt_Stimulation_Stop.Click += new System.EventHandler(this.bt_Stimulation_Stop_Click);
            // 
            // bt_Stimulation_Left
            // 
            this.bt_Stimulation_Left.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bt_Stimulation_Left.Location = new System.Drawing.Point(20, 102);
            this.bt_Stimulation_Left.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bt_Stimulation_Left.Name = "bt_Stimulation_Left";
            this.bt_Stimulation_Left.Size = new System.Drawing.Size(117, 63);
            this.bt_Stimulation_Left.TabIndex = 0;
            this.bt_Stimulation_Left.Text = "Left";
            this.bt_Stimulation_Left.UseVisualStyleBackColor = true;
            this.bt_Stimulation_Left.Click += new System.EventHandler(this.bt_Stimulation_Left_Click);
            // 
            // AmbT
            // 
            this.AmbT.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AmbT.Location = new System.Drawing.Point(2438, 1135);
            this.AmbT.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AmbT.Name = "AmbT";
            this.AmbT.ReadOnly = true;
            this.AmbT.Size = new System.Drawing.Size(121, 30);
            this.AmbT.TabIndex = 7;
            this.AmbT.Visible = false;
            // 
            // cbHTPASelect
            // 
            this.cbHTPASelect.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbHTPASelect.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cbHTPASelect.FormattingEnabled = true;
            this.cbHTPASelect.Items.AddRange(new object[] {
            "HTPA8",
            "HTPA32"});
            this.cbHTPASelect.Location = new System.Drawing.Point(2436, 1063);
            this.cbHTPASelect.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbHTPASelect.Name = "cbHTPASelect";
            this.cbHTPASelect.Size = new System.Drawing.Size(126, 33);
            this.cbHTPASelect.TabIndex = 0;
            this.cbHTPASelect.Visible = false;
            // 
            // label71
            // 
            this.label71.AutoSize = true;
            this.label71.Location = new System.Drawing.Point(2438, 1105);
            this.label71.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label71.Name = "label71";
            this.label71.Size = new System.Drawing.Size(70, 20);
            this.label71.TabIndex = 16;
            this.label71.Text = "T sensor";
            this.label71.Visible = false;
            // 
            // label75
            // 
            this.label75.AutoSize = true;
            this.label75.Location = new System.Drawing.Point(2438, 1034);
            this.label75.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label75.Name = "label75";
            this.label75.Size = new System.Drawing.Size(82, 20);
            this.label75.TabIndex = 16;
            this.label75.Text = "IR sensor:";
            this.label75.Visible = false;
            // 
            // CheckBox_IsTheRoachConfined
            // 
            this.CheckBox_IsTheRoachConfined.AutoSize = true;
            this.CheckBox_IsTheRoachConfined.Location = new System.Drawing.Point(2080, 1497);
            this.CheckBox_IsTheRoachConfined.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckBox_IsTheRoachConfined.Name = "CheckBox_IsTheRoachConfined";
            this.CheckBox_IsTheRoachConfined.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.CheckBox_IsTheRoachConfined.Size = new System.Drawing.Size(172, 24);
            this.CheckBox_IsTheRoachConfined.TabIndex = 118;
            this.CheckBox_IsTheRoachConfined.Text = "Confine The Roach";
            this.CheckBox_IsTheRoachConfined.UseVisualStyleBackColor = true;
            // 
            // Button_ReadFlash
            // 
            this.Button_ReadFlash.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_ReadFlash.Location = new System.Drawing.Point(3090, 1234);
            this.Button_ReadFlash.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Button_ReadFlash.Name = "Button_ReadFlash";
            this.Button_ReadFlash.Size = new System.Drawing.Size(117, 68);
            this.Button_ReadFlash.TabIndex = 43;
            this.Button_ReadFlash.Text = "Read Flash";
            this.Button_ReadFlash.UseVisualStyleBackColor = true;
            this.Button_ReadFlash.Click += new System.EventHandler(this.Button_ReadFlash_Click);
            // 
            // label51
            // 
            this.label51.AutoSize = true;
            this.label51.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label51.Location = new System.Drawing.Point(1562, 1322);
            this.label51.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label51.Name = "label51";
            this.label51.Size = new System.Drawing.Size(73, 29);
            this.label51.TabIndex = 130;
            this.label51.Text = "Vicon";
            // 
            // TextCalculatedLinearSpeed_Vicon
            // 
            this.TextCalculatedLinearSpeed_Vicon.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextCalculatedLinearSpeed_Vicon.Location = new System.Drawing.Point(1562, 1352);
            this.TextCalculatedLinearSpeed_Vicon.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextCalculatedLinearSpeed_Vicon.Name = "TextCalculatedLinearSpeed_Vicon";
            this.TextCalculatedLinearSpeed_Vicon.Size = new System.Drawing.Size(64, 35);
            this.TextCalculatedLinearSpeed_Vicon.TabIndex = 128;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.label101);
            this.groupBox6.Controls.Add(this.label53);
            this.groupBox6.Controls.Add(this.label52);
            this.groupBox6.Controls.Add(this.label10);
            this.groupBox6.Controls.Add(this.TextCalculatedAngularSpeed_IMU);
            this.groupBox6.Controls.Add(this.label9);
            this.groupBox6.Controls.Add(this.TextCalculatedLinearSpeed_IMU);
            this.groupBox6.Location = new System.Drawing.Point(1137, 1389);
            this.groupBox6.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox6.Size = new System.Drawing.Size(358, 165);
            this.groupBox6.TabIndex = 119;
            this.groupBox6.TabStop = false;
            // 
            // label101
            // 
            this.label101.AutoSize = true;
            this.label101.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label101.Location = new System.Drawing.Point(12, 62);
            this.label101.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label101.Name = "label101";
            this.label101.Size = new System.Drawing.Size(158, 29);
            this.label101.TabIndex = 74;
            this.label101.Text = "Linear Speed";
            // 
            // label53
            // 
            this.label53.AutoSize = true;
            this.label53.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label53.Location = new System.Drawing.Point(12, 117);
            this.label53.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label53.Name = "label53";
            this.label53.Size = new System.Drawing.Size(173, 29);
            this.label53.TabIndex = 88;
            this.label53.Text = "Angular Speed";
            // 
            // label52
            // 
            this.label52.AutoSize = true;
            this.label52.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label52.Location = new System.Drawing.Point(192, 22);
            this.label52.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label52.Name = "label52";
            this.label52.Size = new System.Drawing.Size(56, 29);
            this.label52.TabIndex = 97;
            this.label52.Text = "IMU";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(280, 118);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(74, 29);
            this.label10.TabIndex = 93;
            this.label10.Text = "deg/s";
            // 
            // TextCalculatedAngularSpeed_IMU
            // 
            this.TextCalculatedAngularSpeed_IMU.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.TextCalculatedAngularSpeed_IMU.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextCalculatedAngularSpeed_IMU.Location = new System.Drawing.Point(177, 112);
            this.TextCalculatedAngularSpeed_IMU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextCalculatedAngularSpeed_IMU.Name = "TextCalculatedAngularSpeed_IMU";
            this.TextCalculatedAngularSpeed_IMU.Size = new System.Drawing.Size(80, 35);
            this.TextCalculatedAngularSpeed_IMU.TabIndex = 95;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(280, 62);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(64, 29);
            this.label9.TabIndex = 92;
            this.label9.Text = "cm/s";
            // 
            // TextCalculatedLinearSpeed_IMU
            // 
            this.TextCalculatedLinearSpeed_IMU.BackColor = System.Drawing.SystemColors.InactiveBorder;
            this.TextCalculatedLinearSpeed_IMU.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextCalculatedLinearSpeed_IMU.Location = new System.Drawing.Point(177, 57);
            this.TextCalculatedLinearSpeed_IMU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextCalculatedLinearSpeed_IMU.Name = "TextCalculatedLinearSpeed_IMU";
            this.TextCalculatedLinearSpeed_IMU.Size = new System.Drawing.Size(80, 35);
            this.TextCalculatedLinearSpeed_IMU.TabIndex = 94;
            // 
            // TextCalculatedAngularSpeed_Vicon
            // 
            this.TextCalculatedAngularSpeed_Vicon.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextCalculatedAngularSpeed_Vicon.Location = new System.Drawing.Point(1562, 1409);
            this.TextCalculatedAngularSpeed_Vicon.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextCalculatedAngularSpeed_Vicon.Name = "TextCalculatedAngularSpeed_Vicon";
            this.TextCalculatedAngularSpeed_Vicon.Size = new System.Drawing.Size(64, 35);
            this.TextCalculatedAngularSpeed_Vicon.TabIndex = 129;
            // 
            // GroupBoxControl_NavigationStartStop
            // 
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.CheckClickToSaveFlash);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.Navigation_Start);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.Navigation_Stop);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.SelectionOfGUITimer);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.Button_UpdateGUITimer);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.TextBox_FileName);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.CheckClickToMute);
            this.GroupBoxControl_NavigationStartStop.Controls.Add(this.ClickToLogFile);
            this.GroupBoxControl_NavigationStartStop.Location = new System.Drawing.Point(2066, 1520);
            this.GroupBoxControl_NavigationStartStop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationStartStop.Name = "GroupBoxControl_NavigationStartStop";
            this.GroupBoxControl_NavigationStartStop.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationStartStop.Size = new System.Drawing.Size(454, 271);
            this.GroupBoxControl_NavigationStartStop.TabIndex = 119;
            this.GroupBoxControl_NavigationStartStop.TabStop = false;
            // 
            // CheckClickToSaveFlash
            // 
            this.CheckClickToSaveFlash.AutoSize = true;
            this.CheckClickToSaveFlash.Location = new System.Drawing.Point(216, 66);
            this.CheckClickToSaveFlash.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckClickToSaveFlash.Name = "CheckClickToSaveFlash";
            this.CheckClickToSaveFlash.Size = new System.Drawing.Size(173, 24);
            this.CheckClickToSaveFlash.TabIndex = 117;
            this.CheckClickToSaveFlash.Text = "Click To Save Flash";
            this.CheckClickToSaveFlash.UseVisualStyleBackColor = true;
            // 
            // Navigation_Start
            // 
            this.Navigation_Start.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.Navigation_Start.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Navigation_Start.Location = new System.Drawing.Point(237, 177);
            this.Navigation_Start.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Start.Name = "Navigation_Start";
            this.Navigation_Start.Size = new System.Drawing.Size(214, 82);
            this.Navigation_Start.TabIndex = 41;
            this.Navigation_Start.Text = "Navigation Start 0x40";
            this.Navigation_Start.UseVisualStyleBackColor = false;
            this.Navigation_Start.Click += new System.EventHandler(this.Navigation_Start_Click);
            // 
            // Navigation_Stop
            // 
            this.Navigation_Stop.BackColor = System.Drawing.Color.Gray;
            this.Navigation_Stop.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Navigation_Stop.Location = new System.Drawing.Point(9, 177);
            this.Navigation_Stop.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Stop.Name = "Navigation_Stop";
            this.Navigation_Stop.Size = new System.Drawing.Size(219, 80);
            this.Navigation_Stop.TabIndex = 40;
            this.Navigation_Stop.Text = "Navigation Stop 0x49";
            this.Navigation_Stop.UseVisualStyleBackColor = false;
            this.Navigation_Stop.Click += new System.EventHandler(this.Navigation_Stop_Click);
            // 
            // SelectionOfGUITimer
            // 
            this.SelectionOfGUITimer.FormattingEnabled = true;
            this.SelectionOfGUITimer.Items.AddRange(new object[] {
            "15",
            "20",
            "25",
            "30"});
            this.SelectionOfGUITimer.Location = new System.Drawing.Point(279, 114);
            this.SelectionOfGUITimer.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SelectionOfGUITimer.Name = "SelectionOfGUITimer";
            this.SelectionOfGUITimer.Size = new System.Drawing.Size(91, 28);
            this.SelectionOfGUITimer.TabIndex = 20;
            // 
            // Button_UpdateGUITimer
            // 
            this.Button_UpdateGUITimer.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_UpdateGUITimer.Location = new System.Drawing.Point(16, 114);
            this.Button_UpdateGUITimer.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Button_UpdateGUITimer.Name = "Button_UpdateGUITimer";
            this.Button_UpdateGUITimer.Size = new System.Drawing.Size(242, 52);
            this.Button_UpdateGUITimer.TabIndex = 116;
            this.Button_UpdateGUITimer.Text = "Update GUI Timer";
            this.Button_UpdateGUITimer.UseVisualStyleBackColor = true;
            this.Button_UpdateGUITimer.Click += new System.EventHandler(this.Button_UpdateGUITimer_Click);
            // 
            // TextBox_FileName
            // 
            this.TextBox_FileName.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBox_FileName.Location = new System.Drawing.Point(216, 23);
            this.TextBox_FileName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBox_FileName.Name = "TextBox_FileName";
            this.TextBox_FileName.Size = new System.Drawing.Size(226, 26);
            this.TextBox_FileName.TabIndex = 115;
            // 
            // CheckClickToMute
            // 
            this.CheckClickToMute.AutoSize = true;
            this.CheckClickToMute.Location = new System.Drawing.Point(16, 66);
            this.CheckClickToMute.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.CheckClickToMute.Name = "CheckClickToMute";
            this.CheckClickToMute.Size = new System.Drawing.Size(130, 24);
            this.CheckClickToMute.TabIndex = 113;
            this.CheckClickToMute.Text = "Click To Mute";
            this.CheckClickToMute.UseVisualStyleBackColor = true;
            this.CheckClickToMute.CheckedChanged += new System.EventHandler(this.CheckClickToMute_CheckedChanged);
            // 
            // ClickToLogFile
            // 
            this.ClickToLogFile.AutoSize = true;
            this.ClickToLogFile.Enabled = false;
            this.ClickToLogFile.Location = new System.Drawing.Point(16, 25);
            this.ClickToLogFile.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ClickToLogFile.Name = "ClickToLogFile";
            this.ClickToLogFile.Size = new System.Drawing.Size(150, 24);
            this.ClickToLogFile.TabIndex = 94;
            this.ClickToLogFile.Text = "Click To Log File";
            this.ClickToLogFile.UseVisualStyleBackColor = true;
            this.ClickToLogFile.CheckedChanged += new System.EventHandler(this.ClickToLogFile_CheckedChanged);
            // 
            // GroupBoxControl_StimulationIndicator
            // 
            this.GroupBoxControl_StimulationIndicator.Controls.Add(this.StiSignal_Forward);
            this.GroupBoxControl_StimulationIndicator.Controls.Add(this.StiSignal_Right);
            this.GroupBoxControl_StimulationIndicator.Controls.Add(this.StiSignal_Left);
            this.GroupBoxControl_StimulationIndicator.Location = new System.Drawing.Point(1924, 986);
            this.GroupBoxControl_StimulationIndicator.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_StimulationIndicator.Name = "GroupBoxControl_StimulationIndicator";
            this.GroupBoxControl_StimulationIndicator.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_StimulationIndicator.Size = new System.Drawing.Size(358, 205);
            this.GroupBoxControl_StimulationIndicator.TabIndex = 118;
            this.GroupBoxControl_StimulationIndicator.TabStop = false;
            // 
            // StiSignal_Forward
            // 
            this.StiSignal_Forward.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Forward.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Forward.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.StiSignal_Forward.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StiSignal_Forward.Location = new System.Drawing.Point(104, 48);
            this.StiSignal_Forward.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StiSignal_Forward.Name = "StiSignal_Forward";
            this.StiSignal_Forward.Size = new System.Drawing.Size(153, 65);
            this.StiSignal_Forward.TabIndex = 107;
            this.StiSignal_Forward.Text = "Accelerate";
            this.StiSignal_Forward.UseVisualStyleBackColor = false;
            // 
            // StiSignal_Right
            // 
            this.StiSignal_Right.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Right.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Right.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.StiSignal_Right.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StiSignal_Right.Location = new System.Drawing.Point(21, 122);
            this.StiSignal_Right.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StiSignal_Right.Name = "StiSignal_Right";
            this.StiSignal_Right.Size = new System.Drawing.Size(110, 65);
            this.StiSignal_Right.TabIndex = 106;
            this.StiSignal_Right.Text = "Right";
            this.StiSignal_Right.UseVisualStyleBackColor = false;
            // 
            // StiSignal_Left
            // 
            this.StiSignal_Left.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Left.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.StiSignal_Left.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.StiSignal_Left.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StiSignal_Left.Location = new System.Drawing.Point(230, 122);
            this.StiSignal_Left.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.StiSignal_Left.Name = "StiSignal_Left";
            this.StiSignal_Left.Size = new System.Drawing.Size(110, 65);
            this.StiSignal_Left.TabIndex = 105;
            this.StiSignal_Left.Text = "Left";
            this.StiSignal_Left.UseVisualStyleBackColor = false;
            // 
            // Radio_RightCerciLeftSegment
            // 
            this.Radio_RightCerciLeftSegment.AutoSize = true;
            this.Radio_RightCerciLeftSegment.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_RightCerciLeftSegment.Location = new System.Drawing.Point(75, 1229);
            this.Radio_RightCerciLeftSegment.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_RightCerciLeftSegment.Name = "Radio_RightCerciLeftSegment";
            this.Radio_RightCerciLeftSegment.Size = new System.Drawing.Size(261, 26);
            this.Radio_RightCerciLeftSegment.TabIndex = 19;
            this.Radio_RightCerciLeftSegment.TabStop = true;
            this.Radio_RightCerciLeftSegment.Text = "Right Cercus - Left Segment";
            this.Radio_RightCerciLeftSegment.UseVisualStyleBackColor = true;
            this.Radio_RightCerciLeftSegment.CheckedChanged += new System.EventHandler(this.Radio_RightCerciLeftSegment_CheckedChanged);
            // 
            // Radio_RightCerciRightSegment
            // 
            this.Radio_RightCerciRightSegment.AutoSize = true;
            this.Radio_RightCerciRightSegment.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_RightCerciRightSegment.Location = new System.Drawing.Point(75, 1188);
            this.Radio_RightCerciRightSegment.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_RightCerciRightSegment.Name = "Radio_RightCerciRightSegment";
            this.Radio_RightCerciRightSegment.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.Radio_RightCerciRightSegment.Size = new System.Drawing.Size(273, 26);
            this.Radio_RightCerciRightSegment.TabIndex = 18;
            this.Radio_RightCerciRightSegment.TabStop = true;
            this.Radio_RightCerciRightSegment.Text = "Right Cercus - Right Segment";
            this.Radio_RightCerciRightSegment.UseVisualStyleBackColor = true;
            this.Radio_RightCerciRightSegment.CheckedChanged += new System.EventHandler(this.Radio_RightCerciRightSegment_CheckedChanged);
            // 
            // Radio_LeftCerciRightSegment
            // 
            this.Radio_LeftCerciRightSegment.AutoSize = true;
            this.Radio_LeftCerciRightSegment.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_LeftCerciRightSegment.Location = new System.Drawing.Point(75, 1146);
            this.Radio_LeftCerciRightSegment.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_LeftCerciRightSegment.Name = "Radio_LeftCerciRightSegment";
            this.Radio_LeftCerciRightSegment.Size = new System.Drawing.Size(261, 26);
            this.Radio_LeftCerciRightSegment.TabIndex = 17;
            this.Radio_LeftCerciRightSegment.TabStop = true;
            this.Radio_LeftCerciRightSegment.Text = "Left Cercus - Right Segment";
            this.Radio_LeftCerciRightSegment.UseVisualStyleBackColor = true;
            this.Radio_LeftCerciRightSegment.CheckedChanged += new System.EventHandler(this.Radio_LeftCerciRightSegment_CheckedChanged);
            // 
            // Radio_LeftCerciLeftSegment
            // 
            this.Radio_LeftCerciLeftSegment.AutoSize = true;
            this.Radio_LeftCerciLeftSegment.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_LeftCerciLeftSegment.Location = new System.Drawing.Point(75, 1105);
            this.Radio_LeftCerciLeftSegment.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_LeftCerciLeftSegment.Name = "Radio_LeftCerciLeftSegment";
            this.Radio_LeftCerciLeftSegment.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.Radio_LeftCerciLeftSegment.Size = new System.Drawing.Size(249, 26);
            this.Radio_LeftCerciLeftSegment.TabIndex = 16;
            this.Radio_LeftCerciLeftSegment.TabStop = true;
            this.Radio_LeftCerciLeftSegment.Text = "Left Cercus - Left Segment";
            this.Radio_LeftCerciLeftSegment.UseVisualStyleBackColor = true;
            this.Radio_LeftCerciLeftSegment.CheckedChanged += new System.EventHandler(this.Radio_LeftCerciLeftSegment_CheckedChanged);
            // 
            // Radio_BothSegment
            // 
            this.Radio_BothSegment.AutoSize = true;
            this.Radio_BothSegment.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_BothSegment.Location = new System.Drawing.Point(75, 1063);
            this.Radio_BothSegment.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_BothSegment.Name = "Radio_BothSegment";
            this.Radio_BothSegment.Size = new System.Drawing.Size(157, 26);
            this.Radio_BothSegment.TabIndex = 15;
            this.Radio_BothSegment.TabStop = true;
            this.Radio_BothSegment.Text = "Both Segments";
            this.Radio_BothSegment.UseVisualStyleBackColor = true;
            this.Radio_BothSegment.CheckedChanged += new System.EventHandler(this.Radio_BothSegment_CheckedChanged);
            // 
            // Radio_BothCerci
            // 
            this.Radio_BothCerci.AutoSize = true;
            this.Radio_BothCerci.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Radio_BothCerci.Location = new System.Drawing.Point(75, 1022);
            this.Radio_BothCerci.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Radio_BothCerci.Name = "Radio_BothCerci";
            this.Radio_BothCerci.Size = new System.Drawing.Size(119, 26);
            this.Radio_BothCerci.TabIndex = 14;
            this.Radio_BothCerci.TabStop = true;
            this.Radio_BothCerci.Text = "Both Cerci";
            this.Radio_BothCerci.UseVisualStyleBackColor = true;
            this.Radio_BothCerci.CheckedChanged += new System.EventHandler(this.Radio_BothCerci_CheckedChanged);
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.PinConfiguration_CerciInside);
            this.groupBox8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox8.Location = new System.Drawing.Point(675, 1022);
            this.groupBox8.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox8.Size = new System.Drawing.Size(300, 77);
            this.groupBox8.TabIndex = 111;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "Pin Configuration";
            // 
            // PinConfiguration_CerciInside
            // 
            this.PinConfiguration_CerciInside.AutoSize = true;
            this.PinConfiguration_CerciInside.Location = new System.Drawing.Point(38, 34);
            this.PinConfiguration_CerciInside.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.PinConfiguration_CerciInside.Name = "PinConfiguration_CerciInside";
            this.PinConfiguration_CerciInside.Size = new System.Drawing.Size(204, 26);
            this.PinConfiguration_CerciInside.TabIndex = 0;
            this.PinConfiguration_CerciInside.Text = "Cercal Pins are Inner";
            this.PinConfiguration_CerciInside.UseVisualStyleBackColor = true;
            this.PinConfiguration_CerciInside.CheckedChanged += new System.EventHandler(this.PinConfiguration_CerciInside_CheckedChanged);
            // 
            // ClickToVaryV1V2
            // 
            this.ClickToVaryV1V2.AutoSize = true;
            this.ClickToVaryV1V2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ClickToVaryV1V2.Location = new System.Drawing.Point(681, 989);
            this.ClickToVaryV1V2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ClickToVaryV1V2.Name = "ClickToVaryV1V2";
            this.ClickToVaryV1V2.Size = new System.Drawing.Size(258, 26);
            this.ClickToVaryV1V2.TabIndex = 109;
            this.ClickToVaryV1V2.Text = "Click To Differentiate V1 V2";
            this.ClickToVaryV1V2.UseVisualStyleBackColor = true;
            this.ClickToVaryV1V2.CheckedChanged += new System.EventHandler(this.ClickToVaryV1V2_CheckedChanged);
            // 
            // ReadyStimulation
            // 
            this.ReadyStimulation.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.ReadyStimulation.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.ReadyStimulation.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ReadyStimulation.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ReadyStimulation.Location = new System.Drawing.Point(3090, 1145);
            this.ReadyStimulation.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ReadyStimulation.Name = "ReadyStimulation";
            this.ReadyStimulation.Size = new System.Drawing.Size(117, 65);
            this.ReadyStimulation.TabIndex = 114;
            this.ReadyStimulation.Text = " ";
            this.ReadyStimulation.UseVisualStyleBackColor = false;
            this.ReadyStimulation.Click += new System.EventHandler(this.Button_Stimulation_IsKeyBoardReady_Click);
            // 
            // GroupBoxControl_NavigationButton
            // 
            this.GroupBoxControl_NavigationButton.Controls.Add(this.TestSpeed);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.label95);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.SetupLongStimulus);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.comboBox11);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.SetupRight);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.SetupLeft);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.SetupAngleDistance);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.SetupForward);
            this.GroupBoxControl_NavigationButton.Controls.Add(this.NormalStream);
            this.GroupBoxControl_NavigationButton.Location = new System.Drawing.Point(1128, 1195);
            this.GroupBoxControl_NavigationButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationButton.Name = "GroupBoxControl_NavigationButton";
            this.GroupBoxControl_NavigationButton.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationButton.Size = new System.Drawing.Size(1414, 123);
            this.GroupBoxControl_NavigationButton.TabIndex = 112;
            this.GroupBoxControl_NavigationButton.TabStop = false;
            this.GroupBoxControl_NavigationButton.Text = "Navigation";
            // 
            // TestSpeed
            // 
            this.TestSpeed.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TestSpeed.Location = new System.Drawing.Point(882, 31);
            this.TestSpeed.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TestSpeed.Name = "TestSpeed";
            this.TestSpeed.Size = new System.Drawing.Size(142, 77);
            this.TestSpeed.TabIndex = 95;
            this.TestSpeed.Text = "Test speed 0x45";
            this.TestSpeed.UseVisualStyleBackColor = true;
            this.TestSpeed.Click += new System.EventHandler(this.TestSpeed_Click);
            // 
            // label95
            // 
            this.label95.AutoSize = true;
            this.label95.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label95.Location = new System.Drawing.Point(-147, 331);
            this.label95.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label95.Name = "label95";
            this.label95.Size = new System.Drawing.Size(102, 25);
            this.label95.TabIndex = 4;
            this.label95.Text = "Turn Right";
            // 
            // SetupLongStimulus
            // 
            this.SetupLongStimulus.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SetupLongStimulus.Location = new System.Drawing.Point(710, 31);
            this.SetupLongStimulus.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SetupLongStimulus.Name = "SetupLongStimulus";
            this.SetupLongStimulus.Size = new System.Drawing.Size(142, 77);
            this.SetupLongStimulus.TabIndex = 46;
            this.SetupLongStimulus.Text = "Setup Target 0x51";
            this.SetupLongStimulus.UseVisualStyleBackColor = true;
            this.SetupLongStimulus.Click += new System.EventHandler(this.SetupLongStimulus_Click);
            // 
            // comboBox11
            // 
            this.comboBox11.FormattingEnabled = true;
            this.comboBox11.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox11.Location = new System.Drawing.Point(-100, 262);
            this.comboBox11.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox11.Name = "comboBox11";
            this.comboBox11.Size = new System.Drawing.Size(79, 28);
            this.comboBox11.TabIndex = 18;
            // 
            // SetupRight
            // 
            this.SetupRight.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SetupRight.Location = new System.Drawing.Point(20, 31);
            this.SetupRight.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SetupRight.Name = "SetupRight";
            this.SetupRight.Size = new System.Drawing.Size(142, 77);
            this.SetupRight.TabIndex = 39;
            this.SetupRight.Text = "Setup Right 0x42";
            this.SetupRight.UseVisualStyleBackColor = true;
            this.SetupRight.Click += new System.EventHandler(this.SetupRight_Click);
            // 
            // SetupLeft
            // 
            this.SetupLeft.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SetupLeft.Location = new System.Drawing.Point(192, 31);
            this.SetupLeft.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SetupLeft.Name = "SetupLeft";
            this.SetupLeft.Size = new System.Drawing.Size(142, 77);
            this.SetupLeft.TabIndex = 10;
            this.SetupLeft.Text = "Setup Left 0x41";
            this.SetupLeft.UseVisualStyleBackColor = true;
            this.SetupLeft.Click += new System.EventHandler(this.SetupLeft_Click);
            // 
            // SetupAngleDistance
            // 
            this.SetupAngleDistance.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SetupAngleDistance.Location = new System.Drawing.Point(537, 31);
            this.SetupAngleDistance.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SetupAngleDistance.Name = "SetupAngleDistance";
            this.SetupAngleDistance.Size = new System.Drawing.Size(142, 77);
            this.SetupAngleDistance.TabIndex = 41;
            this.SetupAngleDistance.Text = "Setup Parameter 0x50";
            this.SetupAngleDistance.UseVisualStyleBackColor = true;
            this.SetupAngleDistance.Click += new System.EventHandler(this.SetupAngleDistance_Click);
            // 
            // SetupForward
            // 
            this.SetupForward.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SetupForward.Location = new System.Drawing.Point(364, 31);
            this.SetupForward.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.SetupForward.Name = "SetupForward";
            this.SetupForward.Size = new System.Drawing.Size(142, 77);
            this.SetupForward.TabIndex = 40;
            this.SetupForward.Text = "Setup Forward 0x43";
            this.SetupForward.UseVisualStyleBackColor = true;
            this.SetupForward.Click += new System.EventHandler(this.SetupForward_Click);
            // 
            // NormalStream
            // 
            this.NormalStream.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NormalStream.Location = new System.Drawing.Point(1054, 31);
            this.NormalStream.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.NormalStream.Name = "NormalStream";
            this.NormalStream.Size = new System.Drawing.Size(162, 77);
            this.NormalStream.TabIndex = 42;
            this.NormalStream.Text = "0x80";
            this.NormalStream.UseVisualStyleBackColor = true;
            this.NormalStream.Click += new System.EventHandler(this.NormalStream_Click);
            // 
            // GroupBoxControl_NavigationTargets
            // 
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label13);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TargetY2);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TargetX2);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label7);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label6);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TextBox_CockroachY);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TextBox_CockroachX);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TargetY1);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.TargetX1);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label87);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label84);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.label86);
            this.GroupBoxControl_NavigationTargets.Controls.Add(this.comboBox8);
            this.GroupBoxControl_NavigationTargets.Location = new System.Drawing.Point(32, 1609);
            this.GroupBoxControl_NavigationTargets.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationTargets.Name = "GroupBoxControl_NavigationTargets";
            this.GroupBoxControl_NavigationTargets.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationTargets.Size = new System.Drawing.Size(356, 189);
            this.GroupBoxControl_NavigationTargets.TabIndex = 47;
            this.GroupBoxControl_NavigationTargets.TabStop = false;
            this.GroupBoxControl_NavigationTargets.Text = "Targets (Unit cm)";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(260, 35);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(68, 20);
            this.label13.TabIndex = 96;
            this.label13.Text = "Target 2";
            this.label13.Visible = false;
            // 
            // TargetY2
            // 
            this.TargetY2.Location = new System.Drawing.Point(267, 132);
            this.TargetY2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TargetY2.Name = "TargetY2";
            this.TargetY2.Size = new System.Drawing.Size(68, 26);
            this.TargetY2.TabIndex = 95;
            this.TargetY2.Visible = false;
            // 
            // TargetX2
            // 
            this.TargetX2.Location = new System.Drawing.Point(266, 78);
            this.TargetX2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TargetX2.Name = "TargetX2";
            this.TargetX2.Size = new System.Drawing.Size(68, 26);
            this.TargetX2.TabIndex = 94;
            this.TargetX2.Visible = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(158, 37);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(68, 20);
            this.label7.TabIndex = 90;
            this.label7.Text = "Target 1";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(27, 37);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(85, 20);
            this.label6.TabIndex = 89;
            this.label6.Text = "Cockroach";
            // 
            // TextBox_CockroachY
            // 
            this.TextBox_CockroachY.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBox_CockroachY.Location = new System.Drawing.Point(60, 131);
            this.TextBox_CockroachY.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBox_CockroachY.Name = "TextBox_CockroachY";
            this.TextBox_CockroachY.ReadOnly = true;
            this.TextBox_CockroachY.Size = new System.Drawing.Size(68, 30);
            this.TextBox_CockroachY.TabIndex = 66;
            // 
            // TextBox_CockroachX
            // 
            this.TextBox_CockroachX.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBox_CockroachX.Location = new System.Drawing.Point(60, 77);
            this.TextBox_CockroachX.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBox_CockroachX.Name = "TextBox_CockroachX";
            this.TextBox_CockroachX.ReadOnly = true;
            this.TextBox_CockroachX.Size = new System.Drawing.Size(68, 30);
            this.TextBox_CockroachX.TabIndex = 65;
            // 
            // TargetY1
            // 
            this.TargetY1.Location = new System.Drawing.Point(172, 132);
            this.TargetY1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TargetY1.Name = "TargetY1";
            this.TargetY1.Size = new System.Drawing.Size(68, 26);
            this.TargetY1.TabIndex = 63;
            // 
            // TargetX1
            // 
            this.TargetX1.Location = new System.Drawing.Point(171, 78);
            this.TargetX1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TargetX1.Name = "TargetX1";
            this.TargetX1.Size = new System.Drawing.Size(68, 26);
            this.TargetX1.TabIndex = 61;
            // 
            // label87
            // 
            this.label87.AutoSize = true;
            this.label87.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label87.Location = new System.Drawing.Point(15, 140);
            this.label87.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label87.Name = "label87";
            this.label87.Size = new System.Drawing.Size(22, 22);
            this.label87.TabIndex = 60;
            this.label87.Text = "Y";
            // 
            // label84
            // 
            this.label84.AutoSize = true;
            this.label84.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label84.Location = new System.Drawing.Point(15, 83);
            this.label84.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label84.Name = "label84";
            this.label84.Size = new System.Drawing.Size(22, 22);
            this.label84.TabIndex = 58;
            this.label84.Text = "X";
            // 
            // label86
            // 
            this.label86.AutoSize = true;
            this.label86.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label86.Location = new System.Drawing.Point(-147, 331);
            this.label86.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label86.Name = "label86";
            this.label86.Size = new System.Drawing.Size(102, 25);
            this.label86.TabIndex = 4;
            this.label86.Text = "Turn Right";
            // 
            // comboBox8
            // 
            this.comboBox8.FormattingEnabled = true;
            this.comboBox8.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox8.Location = new System.Drawing.Point(-100, 262);
            this.comboBox8.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox8.Name = "comboBox8";
            this.comboBox8.Size = new System.Drawing.Size(79, 28);
            this.comboBox8.TabIndex = 18;
            // 
            // GroupBoxControl_NavigationParameters
            // 
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.groupBox9);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.groupBox7);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label15);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label8);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_NoDataPoints);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label14);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_AngularSpeedMethod);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label5);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_ReactionTime);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label12);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_UseEscapeMode);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label11);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_AngularSpeed_Threshold);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label48);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_AllowFreeWalkAfterSteering);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label47);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_FreeTimeAfterSteering);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label46);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_LongStimulusFreeTime2);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label100);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label90);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label98);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_Speed_Duration);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_ControlRate);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label99);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label77);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_LinearSpeed_Threshold);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_Speed_Store);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_FreeTime);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label78);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_ForwardTime);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label76);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_LongStimulusFreeTime);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label74);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_LongStimulusForwardTime);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label73);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_Distance);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label70);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.label72);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.Navigation_Angle);
            this.GroupBoxControl_NavigationParameters.Controls.Add(this.comboBox5);
            this.GroupBoxControl_NavigationParameters.Location = new System.Drawing.Point(26, 1158);
            this.GroupBoxControl_NavigationParameters.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationParameters.Name = "GroupBoxControl_NavigationParameters";
            this.GroupBoxControl_NavigationParameters.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.GroupBoxControl_NavigationParameters.Size = new System.Drawing.Size(1046, 426);
            this.GroupBoxControl_NavigationParameters.TabIndex = 45;
            this.GroupBoxControl_NavigationParameters.TabStop = false;
            this.GroupBoxControl_NavigationParameters.Text = "Navigation Parameters";
            // 
            // groupBox9
            // 
            this.groupBox9.Controls.Add(this.AngularSpeed_Vicon);
            this.groupBox9.Controls.Add(this.AngularSpeed_IMU);
            this.groupBox9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox9.Location = new System.Drawing.Point(748, 288);
            this.groupBox9.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox9.Size = new System.Drawing.Size(278, 60);
            this.groupBox9.TabIndex = 120;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "Angular Speed";
            // 
            // AngularSpeed_Vicon
            // 
            this.AngularSpeed_Vicon.AutoSize = true;
            this.AngularSpeed_Vicon.Location = new System.Drawing.Point(134, 23);
            this.AngularSpeed_Vicon.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AngularSpeed_Vicon.Name = "AngularSpeed_Vicon";
            this.AngularSpeed_Vicon.Size = new System.Drawing.Size(74, 24);
            this.AngularSpeed_Vicon.TabIndex = 3;
            this.AngularSpeed_Vicon.TabStop = true;
            this.AngularSpeed_Vicon.Text = "Vicon";
            this.AngularSpeed_Vicon.UseVisualStyleBackColor = true;
            this.AngularSpeed_Vicon.CheckedChanged += new System.EventHandler(this.AngularSpeed_Vicon_CheckedChanged);
            // 
            // AngularSpeed_IMU
            // 
            this.AngularSpeed_IMU.AutoSize = true;
            this.AngularSpeed_IMU.Location = new System.Drawing.Point(10, 25);
            this.AngularSpeed_IMU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.AngularSpeed_IMU.Name = "AngularSpeed_IMU";
            this.AngularSpeed_IMU.Size = new System.Drawing.Size(64, 24);
            this.AngularSpeed_IMU.TabIndex = 2;
            this.AngularSpeed_IMU.TabStop = true;
            this.AngularSpeed_IMU.Text = "IMU";
            this.AngularSpeed_IMU.UseVisualStyleBackColor = true;
            this.AngularSpeed_IMU.CheckedChanged += new System.EventHandler(this.AngularSpeed_IMU_CheckedChanged);
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.LinearSpeed_Vicon);
            this.groupBox7.Controls.Add(this.LinearSpeed_IMU);
            this.groupBox7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox7.Location = new System.Drawing.Point(748, 209);
            this.groupBox7.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox7.Size = new System.Drawing.Size(278, 60);
            this.groupBox7.TabIndex = 119;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "Linear Speed";
            // 
            // LinearSpeed_Vicon
            // 
            this.LinearSpeed_Vicon.AutoSize = true;
            this.LinearSpeed_Vicon.Location = new System.Drawing.Point(134, 23);
            this.LinearSpeed_Vicon.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.LinearSpeed_Vicon.Name = "LinearSpeed_Vicon";
            this.LinearSpeed_Vicon.Size = new System.Drawing.Size(74, 24);
            this.LinearSpeed_Vicon.TabIndex = 1;
            this.LinearSpeed_Vicon.TabStop = true;
            this.LinearSpeed_Vicon.Text = "Vicon";
            this.LinearSpeed_Vicon.UseVisualStyleBackColor = true;
            this.LinearSpeed_Vicon.CheckedChanged += new System.EventHandler(this.LinearSpeed_Vicon_CheckedChanged);
            // 
            // LinearSpeed_IMU
            // 
            this.LinearSpeed_IMU.AutoSize = true;
            this.LinearSpeed_IMU.Location = new System.Drawing.Point(10, 25);
            this.LinearSpeed_IMU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.LinearSpeed_IMU.Name = "LinearSpeed_IMU";
            this.LinearSpeed_IMU.Size = new System.Drawing.Size(64, 24);
            this.LinearSpeed_IMU.TabIndex = 0;
            this.LinearSpeed_IMU.TabStop = true;
            this.LinearSpeed_IMU.Text = "IMU";
            this.LinearSpeed_IMU.UseVisualStyleBackColor = true;
            this.LinearSpeed_IMU.CheckedChanged += new System.EventHandler(this.LinearSpeed_IMU_CheckedChanged);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.Location = new System.Drawing.Point(783, 132);
            this.label15.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(240, 60);
            this.label15.TabIndex = 108;
            this.label15.Text = "Angular Speed:\r\n1. V = sum(v)/n\r\n2. V = (Angle_Last-Angle_First)/t";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(824, 88);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(112, 22);
            this.label8.TabIndex = 107;
            this.label8.Text = "NoDataPoint";
            // 
            // Navigation_NoDataPoints
            // 
            this.Navigation_NoDataPoints.Location = new System.Drawing.Point(954, 85);
            this.Navigation_NoDataPoints.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_NoDataPoints.Name = "Navigation_NoDataPoints";
            this.Navigation_NoDataPoints.Size = new System.Drawing.Size(70, 26);
            this.Navigation_NoDataPoints.TabIndex = 106;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(744, 40);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(188, 22);
            this.label14.TabIndex = 105;
            this.label14.Text = "AngularSpeed Method";
            // 
            // Navigation_AngularSpeedMethod
            // 
            this.Navigation_AngularSpeedMethod.Location = new System.Drawing.Point(954, 37);
            this.Navigation_AngularSpeedMethod.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_AngularSpeedMethod.Name = "Navigation_AngularSpeedMethod";
            this.Navigation_AngularSpeedMethod.Size = new System.Drawing.Size(70, 26);
            this.Navigation_AngularSpeedMethod.TabIndex = 104;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(490, 180);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(152, 22);
            this.label5.TabIndex = 103;
            this.label5.Text = "Reaction Time (s)";
            // 
            // Navigation_ReactionTime
            // 
            this.Navigation_ReactionTime.Location = new System.Drawing.Point(656, 177);
            this.Navigation_ReactionTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_ReactionTime.Name = "Navigation_ReactionTime";
            this.Navigation_ReactionTime.Size = new System.Drawing.Size(70, 26);
            this.Navigation_ReactionTime.TabIndex = 102;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(396, 371);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(243, 22);
            this.label12.TabIndex = 101;
            this.label12.Text = "UseEscapeMode (1No-2Yes)";
            // 
            // Navigation_UseEscapeMode
            // 
            this.Navigation_UseEscapeMode.Location = new System.Drawing.Point(656, 368);
            this.Navigation_UseEscapeMode.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_UseEscapeMode.Name = "Navigation_UseEscapeMode";
            this.Navigation_UseEscapeMode.Size = new System.Drawing.Size(70, 26);
            this.Navigation_UseEscapeMode.TabIndex = 100;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(375, 323);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(266, 22);
            this.label11.TabIndex = 99;
            this.label11.Text = "Angular speed threshold (deg/s)";
            // 
            // Navigation_AngularSpeed_Threshold
            // 
            this.Navigation_AngularSpeed_Threshold.Location = new System.Drawing.Point(656, 320);
            this.Navigation_AngularSpeed_Threshold.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_AngularSpeed_Threshold.Name = "Navigation_AngularSpeed_Threshold";
            this.Navigation_AngularSpeed_Threshold.Size = new System.Drawing.Size(70, 26);
            this.Navigation_AngularSpeed_Threshold.TabIndex = 98;
            // 
            // label48
            // 
            this.label48.AutoSize = true;
            this.label48.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label48.Location = new System.Drawing.Point(44, 131);
            this.label48.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label48.Name = "label48";
            this.label48.Size = new System.Drawing.Size(245, 22);
            this.label48.TabIndex = 89;
            this.label48.Text = "FreeWalk AfterSteer  (1N/2Y)";
            // 
            // Navigation_AllowFreeWalkAfterSteering
            // 
            this.Navigation_AllowFreeWalkAfterSteering.Location = new System.Drawing.Point(297, 126);
            this.Navigation_AllowFreeWalkAfterSteering.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_AllowFreeWalkAfterSteering.Name = "Navigation_AllowFreeWalkAfterSteering";
            this.Navigation_AllowFreeWalkAfterSteering.Size = new System.Drawing.Size(70, 26);
            this.Navigation_AllowFreeWalkAfterSteering.TabIndex = 88;
            // 
            // label47
            // 
            this.label47.AutoSize = true;
            this.label47.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label47.Location = new System.Drawing.Point(88, 180);
            this.label47.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label47.Name = "label47";
            this.label47.Size = new System.Drawing.Size(195, 22);
            this.label47.TabIndex = 87;
            this.label47.Text = "Freetime After Steering";
            // 
            // Navigation_FreeTimeAfterSteering
            // 
            this.Navigation_FreeTimeAfterSteering.Location = new System.Drawing.Point(297, 174);
            this.Navigation_FreeTimeAfterSteering.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_FreeTimeAfterSteering.Name = "Navigation_FreeTimeAfterSteering";
            this.Navigation_FreeTimeAfterSteering.Size = new System.Drawing.Size(70, 26);
            this.Navigation_FreeTimeAfterSteering.TabIndex = 86;
            // 
            // label46
            // 
            this.label46.AutoSize = true;
            this.label46.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label46.Location = new System.Drawing.Point(28, 325);
            this.label46.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label46.Name = "label46";
            this.label46.Size = new System.Drawing.Size(251, 22);
            this.label46.TabIndex = 85;
            this.label46.Text = "Free Time 2 (Small Speed) (s)";
            // 
            // Navigation_LongStimulusFreeTime2
            // 
            this.Navigation_LongStimulusFreeTime2.Location = new System.Drawing.Point(297, 317);
            this.Navigation_LongStimulusFreeTime2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_LongStimulusFreeTime2.Name = "Navigation_LongStimulusFreeTime2";
            this.Navigation_LongStimulusFreeTime2.Size = new System.Drawing.Size(70, 26);
            this.Navigation_LongStimulusFreeTime2.TabIndex = 84;
            // 
            // label100
            // 
            this.label100.AutoSize = true;
            this.label100.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label100.Location = new System.Drawing.Point(412, 132);
            this.label100.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label100.Name = "label100";
            this.label100.Size = new System.Drawing.Size(230, 22);
            this.label100.TabIndex = 73;
            this.label100.Text = "Duration to check speed (s)";
            // 
            // label90
            // 
            this.label90.AutoSize = true;
            this.label90.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label90.Location = new System.Drawing.Point(148, 374);
            this.label90.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label90.Name = "label90";
            this.label90.Size = new System.Drawing.Size(137, 22);
            this.label90.TabIndex = 58;
            this.label90.Text = "Control Rate (s)";
            // 
            // label98
            // 
            this.label98.AutoSize = true;
            this.label98.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label98.Location = new System.Drawing.Point(423, 228);
            this.label98.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label98.Name = "label98";
            this.label98.Size = new System.Drawing.Size(218, 22);
            this.label98.TabIndex = 77;
            this.label98.Text = "Window time for speed (s)";
            // 
            // Navigation_Speed_Duration
            // 
            this.Navigation_Speed_Duration.Location = new System.Drawing.Point(656, 129);
            this.Navigation_Speed_Duration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Speed_Duration.Name = "Navigation_Speed_Duration";
            this.Navigation_Speed_Duration.Size = new System.Drawing.Size(70, 26);
            this.Navigation_Speed_Duration.TabIndex = 72;
            // 
            // Navigation_ControlRate
            // 
            this.Navigation_ControlRate.Location = new System.Drawing.Point(297, 365);
            this.Navigation_ControlRate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_ControlRate.Name = "Navigation_ControlRate";
            this.Navigation_ControlRate.Size = new System.Drawing.Size(70, 26);
            this.Navigation_ControlRate.TabIndex = 57;
            // 
            // label99
            // 
            this.label99.AutoSize = true;
            this.label99.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label99.Location = new System.Drawing.Point(392, 275);
            this.label99.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label99.Name = "label99";
            this.label99.Size = new System.Drawing.Size(247, 22);
            this.label99.TabIndex = 75;
            this.label99.Text = "Linear speed threshold (cm/s)";
            // 
            // label77
            // 
            this.label77.AutoSize = true;
            this.label77.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label77.Location = new System.Drawing.Point(526, 85);
            this.label77.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label77.Name = "label77";
            this.label77.Size = new System.Drawing.Size(118, 22);
            this.label77.TabIndex = 56;
            this.label77.Text = "Free Time (s)";
            // 
            // Navigation_LinearSpeed_Threshold
            // 
            this.Navigation_LinearSpeed_Threshold.Location = new System.Drawing.Point(656, 272);
            this.Navigation_LinearSpeed_Threshold.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_LinearSpeed_Threshold.Name = "Navigation_LinearSpeed_Threshold";
            this.Navigation_LinearSpeed_Threshold.Size = new System.Drawing.Size(70, 26);
            this.Navigation_LinearSpeed_Threshold.TabIndex = 74;
            // 
            // Navigation_Speed_Store
            // 
            this.Navigation_Speed_Store.Location = new System.Drawing.Point(656, 225);
            this.Navigation_Speed_Store.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Speed_Store.Name = "Navigation_Speed_Store";
            this.Navigation_Speed_Store.Size = new System.Drawing.Size(70, 26);
            this.Navigation_Speed_Store.TabIndex = 76;
            // 
            // Navigation_FreeTime
            // 
            this.Navigation_FreeTime.Location = new System.Drawing.Point(656, 82);
            this.Navigation_FreeTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_FreeTime.Name = "Navigation_FreeTime";
            this.Navigation_FreeTime.Size = new System.Drawing.Size(70, 26);
            this.Navigation_FreeTime.TabIndex = 55;
            // 
            // label78
            // 
            this.label78.AutoSize = true;
            this.label78.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label78.Location = new System.Drawing.Point(496, 37);
            this.label78.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label78.Name = "label78";
            this.label78.Size = new System.Drawing.Size(147, 22);
            this.label78.TabIndex = 54;
            this.label78.Text = "Forward Time (s)";
            // 
            // Navigation_ForwardTime
            // 
            this.Navigation_ForwardTime.Location = new System.Drawing.Point(656, 34);
            this.Navigation_ForwardTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_ForwardTime.Name = "Navigation_ForwardTime";
            this.Navigation_ForwardTime.Size = new System.Drawing.Size(70, 26);
            this.Navigation_ForwardTime.TabIndex = 53;
            // 
            // label76
            // 
            this.label76.AutoSize = true;
            this.label76.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label76.Location = new System.Drawing.Point(44, 226);
            this.label76.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label76.Name = "label76";
            this.label76.Size = new System.Drawing.Size(236, 22);
            this.label76.TabIndex = 52;
            this.label76.Text = "Free Time (Small Speed) (s)";
            // 
            // Navigation_LongStimulusFreeTime
            // 
            this.Navigation_LongStimulusFreeTime.Location = new System.Drawing.Point(297, 222);
            this.Navigation_LongStimulusFreeTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_LongStimulusFreeTime.Name = "Navigation_LongStimulusFreeTime";
            this.Navigation_LongStimulusFreeTime.Size = new System.Drawing.Size(70, 26);
            this.Navigation_LongStimulusFreeTime.TabIndex = 51;
            // 
            // label74
            // 
            this.label74.AutoSize = true;
            this.label74.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label74.Location = new System.Drawing.Point(9, 275);
            this.label74.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label74.Name = "label74";
            this.label74.Size = new System.Drawing.Size(270, 22);
            this.label74.TabIndex = 50;
            this.label74.Text = "Forward Time (Small Speed)  (s)";
            // 
            // Navigation_LongStimulusForwardTime
            // 
            this.Navigation_LongStimulusForwardTime.Location = new System.Drawing.Point(297, 269);
            this.Navigation_LongStimulusForwardTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_LongStimulusForwardTime.Name = "Navigation_LongStimulusForwardTime";
            this.Navigation_LongStimulusForwardTime.Size = new System.Drawing.Size(70, 26);
            this.Navigation_LongStimulusForwardTime.TabIndex = 49;
            // 
            // label73
            // 
            this.label73.AutoSize = true;
            this.label73.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label73.Location = new System.Drawing.Point(162, 82);
            this.label73.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label73.Name = "label73";
            this.label73.Size = new System.Drawing.Size(120, 22);
            this.label73.TabIndex = 46;
            this.label73.Text = "Distance (cm)";
            // 
            // Navigation_Distance
            // 
            this.Navigation_Distance.Location = new System.Drawing.Point(297, 78);
            this.Navigation_Distance.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Distance.Name = "Navigation_Distance";
            this.Navigation_Distance.Size = new System.Drawing.Size(70, 26);
            this.Navigation_Distance.TabIndex = 45;
            // 
            // label70
            // 
            this.label70.AutoSize = true;
            this.label70.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label70.Location = new System.Drawing.Point(152, 32);
            this.label70.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label70.Name = "label70";
            this.label70.Size = new System.Drawing.Size(132, 22);
            this.label70.TabIndex = 44;
            this.label70.Text = "Angle (Degree)";
            // 
            // label72
            // 
            this.label72.AutoSize = true;
            this.label72.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label72.Location = new System.Drawing.Point(-147, 331);
            this.label72.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label72.Name = "label72";
            this.label72.Size = new System.Drawing.Size(102, 25);
            this.label72.TabIndex = 4;
            this.label72.Text = "Turn Right";
            // 
            // Navigation_Angle
            // 
            this.Navigation_Angle.Location = new System.Drawing.Point(297, 31);
            this.Navigation_Angle.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Navigation_Angle.Name = "Navigation_Angle";
            this.Navigation_Angle.Size = new System.Drawing.Size(70, 26);
            this.Navigation_Angle.TabIndex = 43;
            this.Navigation_Angle.Text = " ";
            // 
            // comboBox5
            // 
            this.comboBox5.FormattingEnabled = true;
            this.comboBox5.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox5.Location = new System.Drawing.Point(-100, 262);
            this.comboBox5.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox5.Name = "comboBox5";
            this.comboBox5.Size = new System.Drawing.Size(79, 28);
            this.comboBox5.TabIndex = 18;
            // 
            // groupBox17
            // 
            this.groupBox17.Controls.Add(this.label3);
            this.groupBox17.Controls.Add(this.label69);
            this.groupBox17.Controls.Add(this.comboBox1);
            this.groupBox17.Controls.Add(this.comboBox2);
            this.groupBox17.Controls.Add(this.comboBox3);
            this.groupBox17.Controls.Add(this.Button_ViconConnection);
            this.groupBox17.Controls.Add(this.TextBox_ViconStatus);
            this.groupBox17.Location = new System.Drawing.Point(1458, 1063);
            this.groupBox17.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox17.Name = "groupBox17";
            this.groupBox17.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox17.Size = new System.Drawing.Size(388, 92);
            this.groupBox17.TabIndex = 37;
            this.groupBox17.TabStop = false;
            this.groupBox17.Text = "Vicon Connection";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(9, 448);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 25);
            this.label3.TabIndex = 4;
            this.label3.Text = "Forward";
            // 
            // label69
            // 
            this.label69.AutoSize = true;
            this.label69.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label69.Location = new System.Drawing.Point(-147, 331);
            this.label69.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label69.Name = "label69";
            this.label69.Size = new System.Drawing.Size(102, 25);
            this.label69.TabIndex = 4;
            this.label69.Text = "Turn Right";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox1.Location = new System.Drawing.Point(86, 412);
            this.comboBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(79, 28);
            this.comboBox1.TabIndex = 18;
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox2.Location = new System.Drawing.Point(-100, 262);
            this.comboBox2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(79, 28);
            this.comboBox2.TabIndex = 18;
            // 
            // comboBox3
            // 
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox3.Location = new System.Drawing.Point(-75, 412);
            this.comboBox3.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(79, 28);
            this.comboBox3.TabIndex = 18;
            // 
            // Button_ViconConnection
            // 
            this.Button_ViconConnection.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Button_ViconConnection.Location = new System.Drawing.Point(14, 35);
            this.Button_ViconConnection.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Button_ViconConnection.Name = "Button_ViconConnection";
            this.Button_ViconConnection.Size = new System.Drawing.Size(93, 51);
            this.Button_ViconConnection.TabIndex = 27;
            this.Button_ViconConnection.Text = "Open";
            this.Button_ViconConnection.UseVisualStyleBackColor = true;
            this.Button_ViconConnection.Click += new System.EventHandler(this.Button_ViconConnection_Click);
            // 
            // TextBox_ViconStatus
            // 
            this.TextBox_ViconStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBox_ViconStatus.Location = new System.Drawing.Point(116, 43);
            this.TextBox_ViconStatus.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBox_ViconStatus.Name = "TextBox_ViconStatus";
            this.TextBox_ViconStatus.ReadOnly = true;
            this.TextBox_ViconStatus.Size = new System.Drawing.Size(254, 26);
            this.TextBox_ViconStatus.TabIndex = 16;
            this.TextBox_ViconStatus.Text = "Not Connected";
            // 
            // Timer1
            // 
            this.Timer1.Tick += new System.EventHandler(this.Timer1_Tick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.IMU_Text_Speed);
            this.groupBox1.Controls.Add(this.IMU_Text_Omega);
            this.groupBox1.Controls.Add(this.label65);
            this.groupBox1.Controls.Add(this.label66);
            this.groupBox1.Controls.Add(this.IMU_Text_Gain);
            this.groupBox1.Controls.Add(this.label50);
            this.groupBox1.Controls.Add(this.IMU_Text_SpeedZ);
            this.groupBox1.Controls.Add(this.IMU_Text_SpeedY);
            this.groupBox1.Controls.Add(this.IMU_Text_SpeedX);
            this.groupBox1.Controls.Add(this.IMU_Text_AccZ);
            this.groupBox1.Controls.Add(this.IMU_Text_AccY);
            this.groupBox1.Controls.Add(this.IMU_Text_AccX);
            this.groupBox1.Controls.Add(this.IMU_Text_Bias);
            this.groupBox1.Controls.Add(this.IMU_Text_Roll);
            this.groupBox1.Controls.Add(this.IMU_Text_Yaw);
            this.groupBox1.Controls.Add(this.label49);
            this.groupBox1.Controls.Add(this.label16);
            this.groupBox1.Controls.Add(this.label17);
            this.groupBox1.Controls.Add(this.IMU_Text_Pitch);
            this.groupBox1.Controls.Add(this.label18);
            this.groupBox1.Controls.Add(this.label19);
            this.groupBox1.Controls.Add(this.label20);
            this.groupBox1.Controls.Add(this.label21);
            this.groupBox1.Controls.Add(this.label22);
            this.groupBox1.Controls.Add(this.label23);
            this.groupBox1.Controls.Add(this.label45);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(1772, 1328);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Size = new System.Drawing.Size(244, 572);
            this.groupBox1.TabIndex = 105;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "IMU (cm/s and degree/s)";
            // 
            // IMU_Text_Speed
            // 
            this.IMU_Text_Speed.Location = new System.Drawing.Point(116, 535);
            this.IMU_Text_Speed.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Speed.Name = "IMU_Text_Speed";
            this.IMU_Text_Speed.ReadOnly = true;
            this.IMU_Text_Speed.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Speed.TabIndex = 78;
            // 
            // IMU_Text_Omega
            // 
            this.IMU_Text_Omega.Location = new System.Drawing.Point(116, 494);
            this.IMU_Text_Omega.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Omega.Name = "IMU_Text_Omega";
            this.IMU_Text_Omega.ReadOnly = true;
            this.IMU_Text_Omega.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Omega.TabIndex = 77;
            // 
            // label65
            // 
            this.label65.AutoSize = true;
            this.label65.Location = new System.Drawing.Point(10, 535);
            this.label65.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label65.Name = "label65";
            this.label65.Size = new System.Drawing.Size(62, 22);
            this.label65.TabIndex = 76;
            this.label65.Text = "Speed";
            // 
            // label66
            // 
            this.label66.AutoSize = true;
            this.label66.Location = new System.Drawing.Point(10, 494);
            this.label66.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label66.Name = "label66";
            this.label66.Size = new System.Drawing.Size(68, 22);
            this.label66.TabIndex = 75;
            this.label66.Text = "Omega";
            // 
            // IMU_Text_Gain
            // 
            this.IMU_Text_Gain.Location = new System.Drawing.Point(116, 454);
            this.IMU_Text_Gain.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Gain.Name = "IMU_Text_Gain";
            this.IMU_Text_Gain.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Gain.TabIndex = 74;
            // 
            // label50
            // 
            this.label50.AutoSize = true;
            this.label50.Location = new System.Drawing.Point(10, 454);
            this.label50.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label50.Name = "label50";
            this.label50.Size = new System.Drawing.Size(48, 22);
            this.label50.TabIndex = 22;
            this.label50.Text = "Gain";
            // 
            // IMU_Text_SpeedZ
            // 
            this.IMU_Text_SpeedZ.Location = new System.Drawing.Point(116, 412);
            this.IMU_Text_SpeedZ.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_SpeedZ.Name = "IMU_Text_SpeedZ";
            this.IMU_Text_SpeedZ.ReadOnly = true;
            this.IMU_Text_SpeedZ.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_SpeedZ.TabIndex = 21;
            // 
            // IMU_Text_SpeedY
            // 
            this.IMU_Text_SpeedY.Location = new System.Drawing.Point(116, 371);
            this.IMU_Text_SpeedY.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_SpeedY.Name = "IMU_Text_SpeedY";
            this.IMU_Text_SpeedY.ReadOnly = true;
            this.IMU_Text_SpeedY.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_SpeedY.TabIndex = 20;
            // 
            // IMU_Text_SpeedX
            // 
            this.IMU_Text_SpeedX.Location = new System.Drawing.Point(116, 329);
            this.IMU_Text_SpeedX.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_SpeedX.Name = "IMU_Text_SpeedX";
            this.IMU_Text_SpeedX.ReadOnly = true;
            this.IMU_Text_SpeedX.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_SpeedX.TabIndex = 19;
            // 
            // IMU_Text_AccZ
            // 
            this.IMU_Text_AccZ.Location = new System.Drawing.Point(116, 288);
            this.IMU_Text_AccZ.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_AccZ.Name = "IMU_Text_AccZ";
            this.IMU_Text_AccZ.ReadOnly = true;
            this.IMU_Text_AccZ.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_AccZ.TabIndex = 18;
            // 
            // IMU_Text_AccY
            // 
            this.IMU_Text_AccY.Location = new System.Drawing.Point(116, 246);
            this.IMU_Text_AccY.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_AccY.Name = "IMU_Text_AccY";
            this.IMU_Text_AccY.ReadOnly = true;
            this.IMU_Text_AccY.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_AccY.TabIndex = 17;
            // 
            // IMU_Text_AccX
            // 
            this.IMU_Text_AccX.Location = new System.Drawing.Point(116, 205);
            this.IMU_Text_AccX.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_AccX.Name = "IMU_Text_AccX";
            this.IMU_Text_AccX.ReadOnly = true;
            this.IMU_Text_AccX.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_AccX.TabIndex = 16;
            // 
            // IMU_Text_Bias
            // 
            this.IMU_Text_Bias.Location = new System.Drawing.Point(116, 163);
            this.IMU_Text_Bias.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Bias.Name = "IMU_Text_Bias";
            this.IMU_Text_Bias.ReadOnly = true;
            this.IMU_Text_Bias.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Bias.TabIndex = 15;
            // 
            // IMU_Text_Roll
            // 
            this.IMU_Text_Roll.Location = new System.Drawing.Point(116, 122);
            this.IMU_Text_Roll.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Roll.Name = "IMU_Text_Roll";
            this.IMU_Text_Roll.ReadOnly = true;
            this.IMU_Text_Roll.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Roll.TabIndex = 14;
            // 
            // IMU_Text_Yaw
            // 
            this.IMU_Text_Yaw.Location = new System.Drawing.Point(116, 38);
            this.IMU_Text_Yaw.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Yaw.Name = "IMU_Text_Yaw";
            this.IMU_Text_Yaw.ReadOnly = true;
            this.IMU_Text_Yaw.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Yaw.TabIndex = 13;
            // 
            // label49
            // 
            this.label49.AutoSize = true;
            this.label49.Location = new System.Drawing.Point(10, 412);
            this.label49.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label49.Name = "label49";
            this.label49.Size = new System.Drawing.Size(78, 22);
            this.label49.TabIndex = 12;
            this.label49.Text = "Speed Z";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(10, 371);
            this.label16.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(79, 22);
            this.label16.TabIndex = 11;
            this.label16.Text = "Speed Y";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(10, 329);
            this.label17.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(79, 22);
            this.label17.TabIndex = 9;
            this.label17.Text = "Speed X";
            // 
            // IMU_Text_Pitch
            // 
            this.IMU_Text_Pitch.Location = new System.Drawing.Point(116, 80);
            this.IMU_Text_Pitch.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.IMU_Text_Pitch.Name = "IMU_Text_Pitch";
            this.IMU_Text_Pitch.ReadOnly = true;
            this.IMU_Text_Pitch.Size = new System.Drawing.Size(98, 28);
            this.IMU_Text_Pitch.TabIndex = 2;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(10, 288);
            this.label18.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(51, 22);
            this.label18.TabIndex = 3;
            this.label18.Text = "AccZ";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(10, 246);
            this.label19.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(52, 22);
            this.label19.TabIndex = 3;
            this.label19.Text = "AccY";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(10, 205);
            this.label20.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(52, 22);
            this.label20.TabIndex = 3;
            this.label20.Text = "AccX";
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(10, 163);
            this.label21.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(45, 22);
            this.label21.TabIndex = 3;
            this.label21.Text = "Bias";
            // 
            // label22
            // 
            this.label22.AutoSize = true;
            this.label22.Location = new System.Drawing.Point(10, 122);
            this.label22.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label22.Name = "label22";
            this.label22.Size = new System.Drawing.Size(41, 22);
            this.label22.TabIndex = 3;
            this.label22.Text = "Roll";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(10, 38);
            this.label23.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(45, 22);
            this.label23.TabIndex = 3;
            this.label23.Text = "Yaw";
            // 
            // label45
            // 
            this.label45.AutoSize = true;
            this.label45.Location = new System.Drawing.Point(10, 80);
            this.label45.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label45.Name = "label45";
            this.label45.Size = new System.Drawing.Size(50, 22);
            this.label45.TabIndex = 3;
            this.label45.Text = "Pitch";
            // 
            // btHMfound_GUI
            // 
            this.btHMfound_GUI.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.btHMfound_GUI.FlatAppearance.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.btHMfound_GUI.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btHMfound_GUI.Location = new System.Drawing.Point(225, 77);
            this.btHMfound_GUI.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btHMfound_GUI.Name = "btHMfound_GUI";
            this.btHMfound_GUI.Size = new System.Drawing.Size(112, 65);
            this.btHMfound_GUI.TabIndex = 21;
            this.btHMfound_GUI.Text = "Found";
            this.btHMfound_GUI.UseVisualStyleBackColor = false;
            // 
            // ShouldWeUseHumanDetectionGUI
            // 
            this.ShouldWeUseHumanDetectionGUI.AutoSize = true;
            this.ShouldWeUseHumanDetectionGUI.Location = new System.Drawing.Point(18, 38);
            this.ShouldWeUseHumanDetectionGUI.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ShouldWeUseHumanDetectionGUI.Name = "ShouldWeUseHumanDetectionGUI";
            this.ShouldWeUseHumanDetectionGUI.Size = new System.Drawing.Size(192, 24);
            this.ShouldWeUseHumanDetectionGUI.TabIndex = 14;
            this.ShouldWeUseHumanDetectionGUI.Text = "Enable GUI Detection";
            this.ShouldWeUseHumanDetectionGUI.UseVisualStyleBackColor = true;
            // 
            // TextBoxHumanDetectionScoreMCU
            // 
            this.TextBoxHumanDetectionScoreMCU.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBoxHumanDetectionScoreMCU.Location = new System.Drawing.Point(120, 217);
            this.TextBoxHumanDetectionScoreMCU.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBoxHumanDetectionScoreMCU.Name = "TextBoxHumanDetectionScoreMCU";
            this.TextBoxHumanDetectionScoreMCU.ReadOnly = true;
            this.TextBoxHumanDetectionScoreMCU.Size = new System.Drawing.Size(70, 30);
            this.TextBoxHumanDetectionScoreMCU.TabIndex = 125;
            // 
            // textGUIThreshold
            // 
            this.textGUIThreshold.Location = new System.Drawing.Point(18, 94);
            this.textGUIThreshold.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textGUIThreshold.Name = "textGUIThreshold";
            this.textGUIThreshold.Size = new System.Drawing.Size(70, 26);
            this.textGUIThreshold.TabIndex = 126;
            // 
            // TextBoxScore
            // 
            this.TextBoxScore.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TextBoxScore.Location = new System.Drawing.Point(122, 92);
            this.TextBoxScore.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.TextBoxScore.Name = "TextBoxScore";
            this.TextBoxScore.ReadOnly = true;
            this.TextBoxScore.Size = new System.Drawing.Size(70, 30);
            this.TextBoxScore.TabIndex = 127;
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.label85);
            this.groupBox11.Controls.Add(this.NumberOfPixelInRange);
            this.groupBox11.Controls.Add(this.label83);
            this.groupBox11.Controls.Add(this.label79);
            this.groupBox11.Controls.Add(this.label81);
            this.groupBox11.Controls.Add(this.MaxOfRange);
            this.groupBox11.Controls.Add(this.label82);
            this.groupBox11.Controls.Add(this.TextBoxScore);
            this.groupBox11.Controls.Add(this.MinOfRange);
            this.groupBox11.Controls.Add(this.textGUIThreshold);
            this.groupBox11.Controls.Add(this.TextBoxHumanDetectionScoreMCU);
            this.groupBox11.Controls.Add(this.MaxOfTemp);
            this.groupBox11.Controls.Add(this.textMCUThreshold);
            this.groupBox11.Controls.Add(this.label80);
            this.groupBox11.Controls.Add(this.MinOfTemp);
            this.groupBox11.Controls.Add(this.DoWeUseOnBoardHumanDetection);
            this.groupBox11.Controls.Add(this.ShouldWeUseHumanDetectionGUI);
            this.groupBox11.Controls.Add(this.label88);
            this.groupBox11.Controls.Add(this.btHMfound_GUI);
            this.groupBox11.Controls.Add(this.comboBox4);
            this.groupBox11.Location = new System.Drawing.Point(1797, 174);
            this.groupBox11.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox11.Size = new System.Drawing.Size(356, 575);
            this.groupBox11.TabIndex = 97;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "Human Detection";
            // 
            // label85
            // 
            this.label85.AutoSize = true;
            this.label85.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label85.Location = new System.Drawing.Point(117, 534);
            this.label85.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label85.Name = "label85";
            this.label85.Size = new System.Drawing.Size(152, 22);
            this.label85.TabIndex = 143;
            this.label85.Text = "No. Pixel in range";
            // 
            // NumberOfPixelInRange
            // 
            this.NumberOfPixelInRange.Location = new System.Drawing.Point(22, 532);
            this.NumberOfPixelInRange.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.NumberOfPixelInRange.Name = "NumberOfPixelInRange";
            this.NumberOfPixelInRange.Size = new System.Drawing.Size(70, 26);
            this.NumberOfPixelInRange.TabIndex = 142;
            this.NumberOfPixelInRange.Text = " ";
            // 
            // label83
            // 
            this.label83.AutoSize = true;
            this.label83.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label83.Location = new System.Drawing.Point(18, 282);
            this.label83.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label83.Name = "label83";
            this.label83.Size = new System.Drawing.Size(165, 22);
            this.label83.TabIndex = 141;
            this.label83.Text = "IR-related variables";
            // 
            // label79
            // 
            this.label79.AutoSize = true;
            this.label79.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label79.Location = new System.Drawing.Point(117, 482);
            this.label79.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label79.Name = "label79";
            this.label79.Size = new System.Drawing.Size(177, 22);
            this.label79.TabIndex = 140;
            this.label79.Text = "Max of Pixel in range";
            // 
            // label81
            // 
            this.label81.AutoSize = true;
            this.label81.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label81.Location = new System.Drawing.Point(117, 377);
            this.label81.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label81.Name = "label81";
            this.label81.Size = new System.Drawing.Size(99, 22);
            this.label81.TabIndex = 135;
            this.label81.Text = "Temp_Max";
            // 
            // MaxOfRange
            // 
            this.MaxOfRange.Location = new System.Drawing.Point(22, 480);
            this.MaxOfRange.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaxOfRange.Name = "MaxOfRange";
            this.MaxOfRange.Size = new System.Drawing.Size(70, 26);
            this.MaxOfRange.TabIndex = 139;
            this.MaxOfRange.Text = " ";
            // 
            // label82
            // 
            this.label82.AutoSize = true;
            this.label82.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label82.Location = new System.Drawing.Point(117, 429);
            this.label82.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label82.Name = "label82";
            this.label82.Size = new System.Drawing.Size(172, 22);
            this.label82.TabIndex = 137;
            this.label82.Text = "Min of Pixel in range";
            // 
            // MinOfRange
            // 
            this.MinOfRange.Location = new System.Drawing.Point(22, 428);
            this.MinOfRange.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MinOfRange.Name = "MinOfRange";
            this.MinOfRange.Size = new System.Drawing.Size(70, 26);
            this.MinOfRange.TabIndex = 138;
            this.MinOfRange.Text = " ";
            // 
            // MaxOfTemp
            // 
            this.MaxOfTemp.Location = new System.Drawing.Point(22, 375);
            this.MaxOfTemp.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaxOfTemp.Name = "MaxOfTemp";
            this.MaxOfTemp.Size = new System.Drawing.Size(70, 26);
            this.MaxOfTemp.TabIndex = 136;
            this.MaxOfTemp.Text = " ";
            // 
            // textMCUThreshold
            // 
            this.textMCUThreshold.Location = new System.Drawing.Point(18, 218);
            this.textMCUThreshold.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.textMCUThreshold.Name = "textMCUThreshold";
            this.textMCUThreshold.Size = new System.Drawing.Size(70, 26);
            this.textMCUThreshold.TabIndex = 128;
            // 
            // label80
            // 
            this.label80.AutoSize = true;
            this.label80.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label80.Location = new System.Drawing.Point(117, 325);
            this.label80.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label80.Name = "label80";
            this.label80.Size = new System.Drawing.Size(94, 22);
            this.label80.TabIndex = 133;
            this.label80.Text = "Temp_Min";
            // 
            // MinOfTemp
            // 
            this.MinOfTemp.Location = new System.Drawing.Point(22, 323);
            this.MinOfTemp.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MinOfTemp.Name = "MinOfTemp";
            this.MinOfTemp.Size = new System.Drawing.Size(70, 26);
            this.MinOfTemp.TabIndex = 134;
            this.MinOfTemp.Text = " ";
            // 
            // DoWeUseOnBoardHumanDetection
            // 
            this.DoWeUseOnBoardHumanDetection.AutoSize = true;
            this.DoWeUseOnBoardHumanDetection.Location = new System.Drawing.Point(18, 165);
            this.DoWeUseOnBoardHumanDetection.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.DoWeUseOnBoardHumanDetection.Name = "DoWeUseOnBoardHumanDetection";
            this.DoWeUseOnBoardHumanDetection.Size = new System.Drawing.Size(224, 24);
            this.DoWeUseOnBoardHumanDetection.TabIndex = 129;
            this.DoWeUseOnBoardHumanDetection.Text = "Enable Onboard Detection";
            this.DoWeUseOnBoardHumanDetection.UseVisualStyleBackColor = true;
            // 
            // label88
            // 
            this.label88.AutoSize = true;
            this.label88.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label88.Location = new System.Drawing.Point(-147, 331);
            this.label88.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label88.Name = "label88";
            this.label88.Size = new System.Drawing.Size(102, 25);
            this.label88.TabIndex = 4;
            this.label88.Text = "Turn Right";
            // 
            // comboBox4
            // 
            this.comboBox4.FormattingEnabled = true;
            this.comboBox4.Items.AddRange(new object[] {
            "P1",
            "P2",
            "P3",
            "P4"});
            this.comboBox4.Location = new System.Drawing.Point(-100, 262);
            this.comboBox4.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.comboBox4.Name = "comboBox4";
            this.comboBox4.Size = new System.Drawing.Size(79, 28);
            this.comboBox4.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1766, 878);
            this.Controls.Add(this.Radio_RightCerciLeftSegment);
            this.Controls.Add(this.Button_ReadFlash);
            this.Controls.Add(this.Radio_RightCerciRightSegment);
            this.Controls.Add(this.CheckBox_IsTheRoachConfined);
            this.Controls.Add(this.Radio_LeftCerciRightSegment);
            this.Controls.Add(this.GroupBoxControl_NavigationStartStop);
            this.Controls.Add(this.Radio_LeftCerciLeftSegment);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Radio_BothSegment);
            this.Controls.Add(this.groupBox17);
            this.Controls.Add(this.Radio_BothCerci);
            this.Controls.Add(this.label51);
            this.Controls.Add(this.groupBox8);
            this.Controls.Add(this.ClickToVaryV1V2);
            this.Controls.Add(this.AmbT);
            this.Controls.Add(this.cbHTPASelect);
            this.Controls.Add(this.ReadyStimulation);
            this.Controls.Add(this.label71);
            this.Controls.Add(this.label75);
            this.Controls.Add(this.TextCalculatedLinearSpeed_Vicon);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.TextCalculatedAngularSpeed_Vicon);
            this.Controls.Add(this.groupBox11);
            this.Controls.Add(this.groupBox6);
            this.Controls.Add(this.GroupBoxControl_NavigationParameters);
            this.Controls.Add(this.GroupBoxControl_StimulationIndicator);
            this.Controls.Add(this.GroupBoxControl_NavigationButton);
            this.Controls.Add(this.GroupBoxControl_NavigationTargets);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.RightToLeftLayout = true;
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Sensor Reading";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.GroupBoxControl_ChipSelection.ResumeLayout(false);
            this.GroupBoxControl_ChipSelection.PerformLayout();
            this.GroupBoxControl_Setting.ResumeLayout(false);
            this.GroupBoxControl_Setting.PerformLayout();
            this.GroupBoxControl_StimulationConfiguration.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.AccelerationGroup.ResumeLayout(false);
            this.AccelerationGroup.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.Stimulation.ResumeLayout(false);
            this.Stimulation.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.GroupBoxControl_NavigationStartStop.ResumeLayout(false);
            this.GroupBoxControl_NavigationStartStop.PerformLayout();
            this.GroupBoxControl_StimulationIndicator.ResumeLayout(false);
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.GroupBoxControl_NavigationButton.ResumeLayout(false);
            this.GroupBoxControl_NavigationButton.PerformLayout();
            this.GroupBoxControl_NavigationTargets.ResumeLayout(false);
            this.GroupBoxControl_NavigationTargets.PerformLayout();
            this.GroupBoxControl_NavigationParameters.ResumeLayout(false);
            this.GroupBoxControl_NavigationParameters.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox17.ResumeLayout(false);
            this.groupBox17.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        
        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Timer Timer1;
        private System.Windows.Forms.ComboBox CheckBox_SerialPorts;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button Button_Serial_OpenPorts;
        private System.Windows.Forms.Label LabelBox_Serial_Status;
        private System.Windows.Forms.GroupBox GroupBoxControl_Setting;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox CheckBox_Serial_BaudRate;
        private System.Windows.Forms.TextBox tbReceviedData;
        private System.Windows.Forms.CheckBox CheckBox_BlueTooth_AutoLoad;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox TextBox_BatteryVoltage;
        private System.Windows.Forms.GroupBox GroupBoxControl_ChipSelection;
        private System.Windows.Forms.ComboBox cbChipID;
        private System.Windows.Forms.Label label59;
        private System.Windows.Forms.Button Button_BlueToothConnection;
        private System.Windows.Forms.Timer timer2;
        private System.Windows.Forms.Timer timer3;
        private System.Windows.Forms.Button Button_ViconConnection;
        private System.Windows.Forms.TextBox TextBox_ViconStatus;
        private System.Windows.Forms.GroupBox groupBox17;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label69;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.TextBox TextRequestData;
        private System.Windows.Forms.Button NormalStream;
        private System.Windows.Forms.GroupBox GroupBoxControl_NavigationParameters;
        private System.Windows.Forms.Label label77;
        private System.Windows.Forms.TextBox Navigation_FreeTime;
        private System.Windows.Forms.Label label78;
        private System.Windows.Forms.TextBox Navigation_ForwardTime;
        private System.Windows.Forms.Label label76;
        private System.Windows.Forms.TextBox Navigation_LongStimulusFreeTime;
        private System.Windows.Forms.Label label74;
        private System.Windows.Forms.TextBox Navigation_LongStimulusForwardTime;
        private System.Windows.Forms.Label label73;
        private System.Windows.Forms.TextBox Navigation_Distance;
        private System.Windows.Forms.Label label70;
        private System.Windows.Forms.Label label72;
        private System.Windows.Forms.TextBox Navigation_Angle;
        private System.Windows.Forms.ComboBox comboBox5;
        private System.Windows.Forms.GroupBox GroupBoxControl_NavigationTargets;
        private System.Windows.Forms.TextBox TargetY1;
        private System.Windows.Forms.TextBox TargetX1;
        private System.Windows.Forms.Label label87;
        private System.Windows.Forms.Label label84;
        private System.Windows.Forms.Label label86;
        private System.Windows.Forms.ComboBox comboBox8;
        private System.Windows.Forms.TextBox TextBox_CockroachY;
        private System.Windows.Forms.TextBox TextBox_CockroachX;
        private System.Windows.Forms.Label label90;
        private System.Windows.Forms.TextBox Navigation_ControlRate;
        private System.Windows.Forms.Label label100;
        private System.Windows.Forms.Label label98;
        private System.Windows.Forms.TextBox Navigation_Speed_Duration;
        private System.Windows.Forms.TextBox Navigation_Speed_Store;
        private System.Windows.Forms.Label label99;
        private System.Windows.Forms.TextBox Navigation_LinearSpeed_Threshold;
        private System.Windows.Forms.Label label101;
        private System.Windows.Forms.Label label48;
        private System.Windows.Forms.TextBox Navigation_AllowFreeWalkAfterSteering;
        private System.Windows.Forms.Label label47;
        private System.Windows.Forms.TextBox Navigation_FreeTimeAfterSteering;
        private System.Windows.Forms.Label label46;
        private System.Windows.Forms.TextBox Navigation_LongStimulusFreeTime2;
        private System.Windows.Forms.Label label53;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox Navigation_AngularSpeed_Threshold;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox Navigation_UseEscapeMode;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox TargetY2;
        private System.Windows.Forms.TextBox TargetX2;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.CheckBox PinConfiguration_CerciInside;
        private System.Windows.Forms.GroupBox AccelerationGroup;
        private System.Windows.Forms.RadioButton Radio_RightCerciLeftSegment;
        private System.Windows.Forms.RadioButton Radio_RightCerciRightSegment;
        private System.Windows.Forms.RadioButton Radio_LeftCerciRightSegment;
        private System.Windows.Forms.RadioButton Radio_LeftCerciLeftSegment;
        private System.Windows.Forms.RadioButton Radio_BothSegment;
        private System.Windows.Forms.RadioButton Radio_BothCerci;
        private System.Windows.Forms.Label label64;
        private System.Windows.Forms.Label label62;
        private System.Windows.Forms.ComboBox GoFoward_Postion1;
        private System.Windows.Forms.ComboBox GoFoward_Postion2;
        private System.Windows.Forms.CheckBox ClickToVaryV1V2;
        private System.Windows.Forms.ComboBox cbCercusLeft;
        private System.Windows.Forms.ComboBox cbCercusRight;
        private System.Windows.Forms.ComboBox cbLeftPin;
        private System.Windows.Forms.ComboBox cbRightPin;
        private System.Windows.Forms.Button StiSignal_Forward;
        private System.Windows.Forms.Button StiSignal_Right;
        private System.Windows.Forms.Button StiSignal_Left;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label60;
        private System.Windows.Forms.TextBox TurnToRight_V2;
        private System.Windows.Forms.Label label56;
        private System.Windows.Forms.TextBox TurnToRight_V1;
        private System.Windows.Forms.TextBox TurnToRight_Period;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Label label27;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.TextBox TurnToRight_Amplitude;
        private System.Windows.Forms.TextBox TurnToRight_Toff2;
        private System.Windows.Forms.TextBox TurnToRight_Toff1;
        private System.Windows.Forms.TextBox TurnToRight_Ton2;
        private System.Windows.Forms.TextBox TurnToRight_Ton1;
        private System.Windows.Forms.TextBox TurnToRight_Duration;
        private System.Windows.Forms.CheckBox Enable_TurnToRight;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label label58;
        private System.Windows.Forms.TextBox GoForward_V2;
        private System.Windows.Forms.Label label55;
        private System.Windows.Forms.TextBox GoForward_V1;
        private System.Windows.Forms.TextBox GoForward_Period;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.Label label32;
        private System.Windows.Forms.Label label33;
        private System.Windows.Forms.Label label34;
        private System.Windows.Forms.Label label35;
        private System.Windows.Forms.Label label36;
        private System.Windows.Forms.Label label37;
        private System.Windows.Forms.TextBox GoForward_Amplitude;
        private System.Windows.Forms.TextBox GoForward_Toff2;
        private System.Windows.Forms.TextBox GoForward_Toff1;
        private System.Windows.Forms.TextBox GoForward_Ton2;
        private System.Windows.Forms.TextBox GoForward_Ton1;
        private System.Windows.Forms.TextBox GoForward_Duration;
        private System.Windows.Forms.CheckBox Enable_Forward;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Label label57;
        private System.Windows.Forms.TextBox TurnToLeft_V2;
        private System.Windows.Forms.Label label54;
        private System.Windows.Forms.TextBox TurnToLeft_V1;
        private System.Windows.Forms.TextBox TurnToLeft_Period;
        private System.Windows.Forms.Label label38;
        private System.Windows.Forms.Label label39;
        private System.Windows.Forms.Label label40;
        private System.Windows.Forms.Label label41;
        private System.Windows.Forms.Label label42;
        private System.Windows.Forms.Label label43;
        private System.Windows.Forms.Label label44;
        private System.Windows.Forms.TextBox TurnToLeft_Amplitude;
        private System.Windows.Forms.TextBox TurnToLeft_Toff2;
        private System.Windows.Forms.TextBox TurnToLeft_Toff1;
        private System.Windows.Forms.TextBox TurnToLeft_Ton2;
        private System.Windows.Forms.TextBox TurnToLeft_Ton1;
        private System.Windows.Forms.TextBox TurnToLeft_Duration;
        private System.Windows.Forms.CheckBox Enable_TurnToLeft;
        private System.Windows.Forms.GroupBox Stimulation;
        private System.Windows.Forms.Label label63;
        private System.Windows.Forms.Button bt_Stimulation_Right;
        private System.Windows.Forms.Button bt_Stimulation_Forward;
        private System.Windows.Forms.Label label61;
        private System.Windows.Forms.Button bt_Stimulation_Stop;
        private System.Windows.Forms.Button bt_Stimulation_Left;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.GroupBox GroupBoxControl_NavigationButton;
        private System.Windows.Forms.Button TestSpeed;
        private System.Windows.Forms.Button Navigation_Start;
        private System.Windows.Forms.Button Navigation_Stop;
        private System.Windows.Forms.Label label95;
        private System.Windows.Forms.Button SetupLongStimulus;
        private System.Windows.Forms.ComboBox comboBox11;
        private System.Windows.Forms.Button SetupRight;
        private System.Windows.Forms.Button SetupLeft;
        private System.Windows.Forms.Button SetupAngleDistance;
        private System.Windows.Forms.Button SetupForward;
        private System.Windows.Forms.CheckBox ClickToLogFile;
        private System.Windows.Forms.CheckBox CheckClickToMute;
        private System.Windows.Forms.Button ReadyStimulation;
        private System.Windows.Forms.TextBox TextBox_FileName;
        private System.Windows.Forms.ComboBox SelectionOfGUITimer;
        private System.Windows.Forms.Button Button_UpdateGUITimer;
        private System.Windows.Forms.GroupBox GroupBoxControl_NavigationStartStop;
        private System.Windows.Forms.GroupBox GroupBoxControl_StimulationIndicator;
        private System.Windows.Forms.GroupBox GroupBoxControl_StimulationConfiguration;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox Navigation_ReactionTime;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox Navigation_NoDataPoints;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox Navigation_AngularSpeedMethod;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox IMU_Text_Gain;
        private System.Windows.Forms.Label label50;
        private System.Windows.Forms.TextBox IMU_Text_SpeedZ;
        private System.Windows.Forms.TextBox IMU_Text_SpeedY;
        private System.Windows.Forms.TextBox IMU_Text_SpeedX;
        private System.Windows.Forms.TextBox IMU_Text_AccZ;
        private System.Windows.Forms.TextBox IMU_Text_AccY;
        private System.Windows.Forms.TextBox IMU_Text_AccX;
        private System.Windows.Forms.TextBox IMU_Text_Bias;
        private System.Windows.Forms.TextBox IMU_Text_Roll;
        private System.Windows.Forms.TextBox IMU_Text_Yaw;
        private System.Windows.Forms.Label label49;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox IMU_Text_Pitch;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label22;
        private System.Windows.Forms.Label label23;
        private System.Windows.Forms.Label label45;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.TextBox TextCalculatedLinearSpeed_IMU;
        private System.Windows.Forms.TextBox TextCalculatedAngularSpeed_IMU;
        private System.Windows.Forms.Label label52;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.RadioButton AngularSpeed_Vicon;
        private System.Windows.Forms.RadioButton AngularSpeed_IMU;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.RadioButton LinearSpeed_Vicon;
        private System.Windows.Forms.RadioButton LinearSpeed_IMU;
        private System.Windows.Forms.TextBox IMU_Text_Speed;
        private System.Windows.Forms.TextBox IMU_Text_Omega;
        private System.Windows.Forms.Label label65;
        private System.Windows.Forms.Label label66;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.Button btHMfound_GUI;
        private System.Windows.Forms.CheckBox ShouldWeUseHumanDetectionGUI;
        private System.Windows.Forms.Label label67;
        private System.Windows.Forms.TextBox tbTemperaturmin;
        private System.Windows.Forms.Label label68;
        private System.Windows.Forms.TextBox AmbT;
        private System.Windows.Forms.ComboBox cbHTPASelect;
        private System.Windows.Forms.Label label71;
        private System.Windows.Forms.Label label75;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.TextBox tbTemperaturemax;
        private System.Windows.Forms.TextBox TextBoxHumanDetectionScoreMCU;
        private System.Windows.Forms.TextBox textGUIThreshold;
        private System.Windows.Forms.TextBox TextBoxScore;
        private System.Windows.Forms.CheckBox CheckClickToSaveFlash;
        private System.Windows.Forms.Label label51;
        private System.Windows.Forms.TextBox TextCalculatedLinearSpeed_Vicon;
        private System.Windows.Forms.TextBox TextCalculatedAngularSpeed_Vicon;
        private System.Windows.Forms.CheckBox ShouldWeStreamImage;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.Label label88;
        private System.Windows.Forms.ComboBox comboBox4;
        private System.Windows.Forms.CheckBox DoWeUseOnBoardHumanDetection;
        private System.Windows.Forms.TextBox textMCUThreshold;
        private System.Windows.Forms.Button btHMfound_MCU;
        private System.Windows.Forms.Button Button_ReadFlash;
        private System.Windows.Forms.Label label83;
        private System.Windows.Forms.Label label79;
        private System.Windows.Forms.Label label81;
        private System.Windows.Forms.TextBox MaxOfRange;
        private System.Windows.Forms.Label label82;
        private System.Windows.Forms.TextBox MinOfRange;
        private System.Windows.Forms.TextBox MaxOfTemp;
        private System.Windows.Forms.Label label80;
        private System.Windows.Forms.TextBox MinOfTemp;
        private System.Windows.Forms.Label label85;
        private System.Windows.Forms.TextBox NumberOfPixelInRange;
        private System.Windows.Forms.CheckBox CheckBox_IsTheRoachConfined;
        private System.Windows.Forms.Label label89;
        private System.Windows.Forms.TextBox FireWatch_MaxTemp;
        private System.Windows.Forms.CheckBox EnableSound;
        private System.Windows.Forms.CheckBox Gamepad_CheckBox;
    }
}

