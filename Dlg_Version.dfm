object FormVersion: TFormVersion
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Version'
  ClientHeight = 137
  ClientWidth = 417
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object ___pnBase: TPanel
    Left = 0
    Top = 0
    Width = 417
    Height = 137
    Align = alClient
    BevelOuter = bvNone
    Color = 3355443
    ParentBackground = False
    TabOrder = 0
    object lb_Version: TLabel
      Left = 303
      Top = 72
      Width = 90
      Height = 16
      Caption = 'Version : 0.14'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 2262986
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_UpdateDate: TLabel
      Left = 160
      Top = 94
      Width = 231
      Height = 16
      Caption = 'Last Update : 2020-10-28 PM 12:08'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 2262986
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lb_Title_Version: TLabel
      Left = 24
      Top = 30
      Width = 168
      Height = 25
      Caption = 'Simulator Client'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 2262986
      Font.Height = -21
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
end
