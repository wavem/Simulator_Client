object FormMain: TFormMain
  Left = 0
  Top = 0
  Caption = 'Simulator_Client'
  ClientHeight = 708
  ClientWidth = 908
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object dxRibbon1: TdxRibbon
    Left = 0
    Top = 0
    Width = 908
    Height = 126
    BarManager = BarMgr
    ColorSchemeName = 'Blue'
    Contexts = <>
    TabOrder = 0
    TabStop = False
    ExplicitWidth = 852
    object dxRibbon1Tab1: TdxRibbonTab
      Active = True
      Caption = 'dxRibbon1Tab1'
      Groups = <>
      Index = 0
    end
  end
  object ___pnBase: TPanel
    Left = 0
    Top = 126
    Width = 908
    Height = 582
    Align = alClient
    BevelOuter = bvNone
    Color = clBlack
    ParentBackground = False
    TabOrder = 5
    ExplicitLeft = 328
    ExplicitTop = 272
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Notebook_Main: TNotebook
      Left = 0
      Top = 0
      Width = 561
      Height = 582
      Align = alLeft
      TabOrder = 0
      object TPage
        Left = 0
        Top = 0
        Caption = 'Default'
        ExplicitWidth = 150
        ExplicitHeight = 150
        object __pnBase_00_Default: TPanel
          Left = 0
          Top = 0
          Width = 561
          Height = 582
          Align = alClient
          BevelOuter = bvNone
          Color = clWindowFrame
          ParentBackground = False
          TabOrder = 0
          ExplicitLeft = 120
          ExplicitTop = 144
          ExplicitWidth = 185
          ExplicitHeight = 41
        end
      end
      object TPage
        Left = 0
        Top = 0
        HelpContext = 1
        Caption = '1'
        ExplicitWidth = 0
        ExplicitHeight = 0
        object __pnBase_01_: TPanel
          Left = 0
          Top = 0
          Width = 561
          Height = 582
          Align = alClient
          BevelOuter = bvNone
          Color = clCream
          ParentBackground = False
          TabOrder = 0
          ExplicitLeft = 176
          ExplicitTop = 144
          ExplicitWidth = 185
          ExplicitHeight = 41
        end
      end
      object TPage
        Left = 0
        Top = 0
        HelpContext = 2
        Caption = '2'
        ExplicitWidth = 0
        ExplicitHeight = 0
        object __pnBase_02_: TPanel
          Left = 0
          Top = 0
          Width = 561
          Height = 582
          Align = alClient
          BevelOuter = bvNone
          Color = clMedGray
          ParentBackground = False
          TabOrder = 0
          ExplicitLeft = 184
          ExplicitTop = 208
          ExplicitWidth = 185
          ExplicitHeight = 41
        end
      end
      object TPage
        Left = 0
        Top = 0
        HelpContext = 3
        Caption = '3'
        ExplicitWidth = 0
        ExplicitHeight = 0
        object __pnBase_03_: TPanel
          Left = 0
          Top = 0
          Width = 561
          Height = 582
          Align = alClient
          BevelOuter = bvNone
          Color = clYellow
          ParentBackground = False
          TabOrder = 0
          ExplicitLeft = 184
          ExplicitTop = 160
          ExplicitWidth = 185
          ExplicitHeight = 41
        end
      end
      object TPage
        Left = 0
        Top = 0
        HelpContext = 4
        Caption = '4'
        ExplicitWidth = 0
        ExplicitHeight = 0
        object __pnBase_04_: TPanel
          Left = 0
          Top = 0
          Width = 561
          Height = 582
          Align = alClient
          BevelOuter = bvNone
          Color = clActiveCaption
          ParentBackground = False
          TabOrder = 0
          ExplicitLeft = 120
          ExplicitTop = 200
          ExplicitWidth = 185
          ExplicitHeight = 41
        end
      end
    end
    object memo: TAdvMemo
      Left = 656
      Top = 0
      Width = 252
      Height = 582
      Cursor = crIBeam
      ActiveLineSettings.ShowActiveLine = False
      ActiveLineSettings.ShowActiveLineIndicator = False
      Align = alRight
      AutoCompletion.Font.Charset = DEFAULT_CHARSET
      AutoCompletion.Font.Color = clWindowText
      AutoCompletion.Font.Height = -11
      AutoCompletion.Font.Name = 'Tahoma'
      AutoCompletion.Font.Style = []
      AutoCompletion.StartToken = '(.'
      AutoCorrect.Active = True
      AutoHintParameterPosition = hpBelowCode
      BookmarkGlyph.Data = {
        36050000424D3605000000000000360400002800000010000000100000000100
        0800000000000001000000000000000000000001000000000000000000000000
        80000080000000808000800000008000800080800000C0C0C000C0DCC000F0CA
        A6000020400000206000002080000020A0000020C0000020E000004000000040
        20000040400000406000004080000040A0000040C0000040E000006000000060
        20000060400000606000006080000060A0000060C0000060E000008000000080
        20000080400000806000008080000080A0000080C0000080E00000A0000000A0
        200000A0400000A0600000A0800000A0A00000A0C00000A0E00000C0000000C0
        200000C0400000C0600000C0800000C0A00000C0C00000C0E00000E0000000E0
        200000E0400000E0600000E0800000E0A00000E0C00000E0E000400000004000
        20004000400040006000400080004000A0004000C0004000E000402000004020
        20004020400040206000402080004020A0004020C0004020E000404000004040
        20004040400040406000404080004040A0004040C0004040E000406000004060
        20004060400040606000406080004060A0004060C0004060E000408000004080
        20004080400040806000408080004080A0004080C0004080E00040A0000040A0
        200040A0400040A0600040A0800040A0A00040A0C00040A0E00040C0000040C0
        200040C0400040C0600040C0800040C0A00040C0C00040C0E00040E0000040E0
        200040E0400040E0600040E0800040E0A00040E0C00040E0E000800000008000
        20008000400080006000800080008000A0008000C0008000E000802000008020
        20008020400080206000802080008020A0008020C0008020E000804000008040
        20008040400080406000804080008040A0008040C0008040E000806000008060
        20008060400080606000806080008060A0008060C0008060E000808000008080
        20008080400080806000808080008080A0008080C0008080E00080A0000080A0
        200080A0400080A0600080A0800080A0A00080A0C00080A0E00080C0000080C0
        200080C0400080C0600080C0800080C0A00080C0C00080C0E00080E0000080E0
        200080E0400080E0600080E0800080E0A00080E0C00080E0E000C0000000C000
        2000C0004000C0006000C0008000C000A000C000C000C000E000C0200000C020
        2000C0204000C0206000C0208000C020A000C020C000C020E000C0400000C040
        2000C0404000C0406000C0408000C040A000C040C000C040E000C0600000C060
        2000C0604000C0606000C0608000C060A000C060C000C060E000C0800000C080
        2000C0804000C0806000C0808000C080A000C080C000C080E000C0A00000C0A0
        2000C0A04000C0A06000C0A08000C0A0A000C0A0C000C0A0E000C0C00000C0C0
        2000C0C04000C0C06000C0C08000C0C0A000F0FBFF00A4A0A000808080000000
        FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00FDFD25252525
        2525252525252525FDFDFD2E25FFFFFFFFFFFFFFFFFFFF25FDFDFD2525252525
        2525252525252525FDFD9A9AB7B7B7B7B7B7B7B7B7B72525FDFDFD25B7B7B7B7
        B7B7B7B7B7B72525FDFD9A9AB7B7B7B7B7B7B7B7B7B72525FDFDFD25BFB7BFBF
        B7B7B7B7B7B72525FDFD9A9ABFBFBFB7BFBFB7B7B7B72525FDFDFD25BFBFBFBF
        BFB7BFBFB7B72525FDFD9A9ABFBFBFB7BFBFBFB7BFB72525FDFDFD25BFBFBFBF
        BFBFBFBFBFB72525FDFD9A9ABFBFBFBFBFB7BFBFB7B72525FDFDFD25BFBFBFBF
        BFBFBFBFBFB72525FDFD9A9ABFBFBFBFBFBFBFBFBFB725FDFDFDFD2525252525
        25252525252525FDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFDFD}
      BorderStyle = bsSingle
      ClipboardFormats = [cfText]
      CodeFolding.Enabled = False
      CodeFolding.LineColor = clGray
      Ctl3D = False
      DelErase = True
      EnhancedHomeKey = False
      Gutter.Font.Charset = DEFAULT_CHARSET
      Gutter.Font.Color = clWindowText
      Gutter.Font.Height = -13
      Gutter.Font.Name = 'Courier New'
      Gutter.Font.Style = []
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'COURIER NEW'
      Font.Style = []
      HiddenCaret = False
      Lines.Strings = (
        '')
      MarkerList.UseDefaultMarkerImageIndex = False
      MarkerList.DefaultMarkerImageIndex = -1
      MarkerList.ImageTransparentColor = -1
      OleDropTarget = []
      PrintOptions.MarginLeft = 0
      PrintOptions.MarginRight = 0
      PrintOptions.MarginTop = 0
      PrintOptions.MarginBottom = 0
      PrintOptions.PageNr = False
      PrintOptions.PrintLineNumbers = False
      RightMarginColor = 14869218
      ScrollHint = False
      SelColor = clWhite
      SelBkColor = clNavy
      ShowRightMargin = True
      SmartTabs = False
      TabOrder = 1
      TabStop = True
      TrimTrailingSpaces = False
      UILanguage.ScrollHint = 'Row'
      UILanguage.Undo = 'Undo'
      UILanguage.Redo = 'Redo'
      UILanguage.Copy = 'Copy'
      UILanguage.Cut = 'Cut'
      UILanguage.Paste = 'Paste'
      UILanguage.Delete = 'Delete'
      UILanguage.SelectAll = 'Select All'
      UrlStyle.TextColor = clBlue
      UrlStyle.BkColor = clWhite
      UrlStyle.Style = [fsUnderline]
      UseStyler = True
      Version = '3.4.1.0'
      WordWrap = wwNone
    end
  end
  object BarMgr: TdxBarManager
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #47569#51008' '#44256#46357
    Font.Style = []
    Categories.Strings = (
      'Default')
    Categories.ItemsVisibles = (
      2)
    Categories.Visibles = (
      True)
    PopupMenuLinks = <>
    UseSystemFont = True
    Left = 328
    DockControlHeights = (
      0
      0
      0
      0)
  end
end
