object FormDataInputEdit: TFormDataInputEdit
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Data Input Edit'
  ClientHeight = 129
  ClientWidth = 186
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object ___pnBase_DataInputEdit: TPanel
    Left = 0
    Top = 0
    Width = 186
    Height = 129
    Align = alClient
    BevelOuter = bvNone
    Color = 2171169
    ParentBackground = False
    TabOrder = 0
    ExplicitLeft = 72
    ExplicitTop = 56
    ExplicitWidth = 185
    ExplicitHeight = 41
    object ed_Data: TAdvEdit
      Left = 24
      Top = 24
      Width = 136
      Height = 27
      EditAlign = eaRight
      EditType = etNumeric
      EmptyTextStyle = []
      LabelFont.Charset = DEFAULT_CHARSET
      LabelFont.Color = clWindowText
      LabelFont.Height = -11
      LabelFont.Name = 'Tahoma'
      LabelFont.Style = []
      Lookup.Font.Charset = DEFAULT_CHARSET
      Lookup.Font.Color = clWindowText
      Lookup.Font.Height = -11
      Lookup.Font.Name = 'Arial'
      Lookup.Font.Style = []
      Lookup.Separator = ';'
      Color = clWindow
      DoubleBuffered = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '0'
      Visible = True
      Version = '3.3.5.3'
    end
    object btn_Input: TAdvGlassButton
      Left = 40
      Top = 66
      Width = 100
      Height = 32
      Cursor = crHandPoint
      BackColor = 3355443
      Caption = 'INPUT'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 2262986
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ForeColor = clWhite
      GlowColor = clOlive
      InnerBorderColor = 3355443
      OuterBorderColor = cl3DDkShadow
      ParentFont = False
      ShineColor = clGray
      TabOrder = 1
      Version = '1.3.0.2'
      OnClick = btn_InputClick
    end
  end
end
