object RegViewer: TRegViewer
  Left = 823
  Top = 617
  Caption = 'RegViewer'
  ClientHeight = 439
  ClientWidth = 1073
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  DesignSize = (
    1073
    439)
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 320
    Top = 48
    Width = 681
    Height = 21
    TabOrder = 0
  end
  object RadioGroup1: TRadioGroup
    Left = 32
    Top = 48
    Width = 97
    Height = 129
    Caption = 'RadioGroup1'
    ItemIndex = 2
    Items.Strings = (
      'HKCR'
      'HKCU'
      'HKLM'
      'HKU'
      'HKCC')
    TabOrder = 1
  end
  object Button1: TButton
    Left = 40
    Top = 200
    Width = 89
    Height = 33
    Caption = 'Set Root'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 200
    Top = 48
    Width = 97
    Height = 25
    Caption = 'Open Key'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = Button2Click
  end
  object Edit3: TEdit
    Left = 1024
    Top = 48
    Width = 33
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object ListBox1: TListBox
    Left = 208
    Top = 112
    Width = 233
    Height = 297
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnDblClick = ListBox1DblClick
  end
  object StringGrid1: TStringGrid
    Left = 464
    Top = 112
    Width = 613
    Height = 297
    Anchors = [akLeft, akTop, akRight]
    ColCount = 3
    DefaultRowHeight = 20
    RowCount = 10
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object Button3: TButton
    Left = 152
    Top = 48
    Width = 33
    Height = 25
    Caption = 'Up'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    OnClick = Button3Click
  end
end
