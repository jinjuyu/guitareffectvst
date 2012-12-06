/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  18 Jul 2012 10:02:23pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAPPINGSDIALOG_MAPPINGSDIALOG_4E13E9BF__
#define __JUCER_HEADER_MAPPINGSDIALOG_MAPPINGSDIALOG_4E13E9BF__

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"

class Mapping;
class PluginField;
class OscMappingManager;
class MidiMappingManager;

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MappingsDialog  : public Component,
                        public ListBoxModel,
                        public TextEditor::Listener,
                        public ButtonListener
{
public:
    //==============================================================================
    MappingsDialog (MidiMappingManager *manager, OscMappingManager *manager2, AudioProcessorGraph::Node *plugin, Array<Mapping *> maps, PluginField *field);
    ~MappingsDialog();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.

	///	Returns the number of active mappings.
	int getNumRows();
	///	Draws a row.
	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected);
	///	Returns the component for a single row.
	Component *refreshComponentForRow(int rowNumber, bool isRowSelected, Component *existingComponentToUpdate);
	///	So the user can select rows.
	void listBoxItemClicked(int row, const MouseEvent &e);
	///	So the user can deselect rows.
	void backgroundClicked();

	///	So the OscMappingManager can get updated with the correct MIDI over OSC address.
	void textEditorTextChanged(TextEditor &editor);

	///	Sets the indexed mapping's parameter.
	void setParameter(int index, int val);
	///	Sets the indexed mapping's CC.
	void setCc(int index, int val);
	///	Sets the indexed mapping's latch value.
	void setLatch(int index, bool val);
	///	Sets the indexed mapping's lower bound.
	void setLowerBound(int index, float val);
	///	Sets the indexed mapping's upper bound.
	void setUpperBound(int index, float val);
	///	Sets the indexed mapping's OSC address.
	void setAddress(int index, const String& address);
	///	Sets the indexed mapping's OSC parameter index.
	void setOscParameter(int index, int val);

	///	Updates the listbox contents.
	void updateListBox();

    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void buttonClicked (Button* buttonThatWasClicked);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

	///	For sorting the results of mappingsList->getSelectedRows().
	struct MappingComparator
	{
		///	For sorting the results of mappingsList->getSelectedRows().
		int compareElements(int first, int second);
	};

	///	For sorting the results of mappingsList->getSelectedRows().
	MappingComparator comparator;

	///	The MidiMappingsManager for any MidiMappings.
	MidiMappingManager *midiManager;
	///	The OscMappingsManager for any OscMappings.
	OscMappingManager *oscManager;
	///	The plugin this dialog refers to.
	AudioProcessorGraph::Node *pluginNode;
	///	The mappings this dialog displays.
	Array<Mapping *> mappings;
	///	The PluginField to apply any mapping changes to.
	PluginField *pluginField;

    //[/UserVariables]

    //==============================================================================
    ListBox* mappingsList;
    TextButton* addMidiButton;
    TextButton* addOscButton;
    TextButton* deleteButton;
    ToggleButton* overrideMidiButton;
    Label* oscMidiAddressLabel;
    TextEditor* oscMidiAddress;
    Label* oscHintLabel;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MappingsDialog (const MappingsDialog&);
    const MappingsDialog& operator= (const MappingsDialog&);
};


#endif   // __JUCER_HEADER_MAPPINGSDIALOG_MAPPINGSDIALOG_4E13E9BF__
