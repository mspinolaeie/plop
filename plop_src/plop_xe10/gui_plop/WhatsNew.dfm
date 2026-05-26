object WhatsNewForm: TWhatsNewForm
  Left = 739
  Top = 617
  Caption = 'What'#39's New In Plop'
  ClientHeight = 355
  ClientWidth = 579
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object Panel1: TPanel
    Left = 0
    Top = 290
    Width = 579
    Height = 65
    Align = alBottom
    TabOrder = 0
    object Label1: TLabel
      Left = 32
      Top = 16
      Width = 308
      Height = 16
      Caption = 'To see this again, use the menu About->What'#39's New'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object OKButton: TButton
      Left = 368
      Top = 16
      Width = 105
      Height = 25
      Caption = 'OK'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = OKButtonClick
    end
  end
  object RichEdit1: TRichEdit
    Left = 0
    Top = 0
    Width = 579
    Height = 290
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Lines.Strings = (
      'Version 3.0.7 Mar 11 2021'
      '- port to Embarcadaro C++ Builder 10.3'
      '- help file available as PDF'
      ''
      'Version 3.0.6 Mar 8 2021'
      '- added back in refocused focal length on Run form'
      ''
      'Version 3.0.5 Aug 10 2010'
      '- fixed z88 starting in wrong directory'
      '- clear z88 error values when run plop'
      ''
      'Version 3.0.4 Feb 28 2010'
      '- fixed error messages for parts'
      '- added 36 point cell supports by Joe Astro'
      ''
      'Version 3.0.3 Dec 25 2009'
      '- 64 bit install'
      ''
      'Version 3.0.2 Sep 27 2009'
      '- changes to where Plop stores z88 files'
      ''
      'Version 3.0.1 Nov 1 2008'
      
        '- remembers glued or sling in the control file (this will break ' +
        'old files)'
      '- z88 is disabled until file is generated'
      '- z88 prints message to let you know it is running'
      ''
      'Version 3.0.0 Sept 2008'
      ''
      '- now supports 3 D modeling using Z88'
      
        '- can model slings or mirror glued to cell when the cell is tilt' +
        'ed'
      '- can copy pictures to clipboard'
      
        '- parts now include a label to tell which corner is which to ori' +
        'ent the parts'
      '- part dimensions can be saved to image file'
      '- uses less memory and runs faster for large designs'
      ''
      ' '
      ' ')
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
    Zoom = 100
  end
end
