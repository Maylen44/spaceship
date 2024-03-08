#include "config.h"

static std::unordered_map<ConfigField, const char*> argumentsMapping
{
        {ConfigField_WindowResolution_X, "x"},
        {ConfigField_WindowResolution_Y, "y"},
        {ConfigField_TimeRate_001, "rate001"},
        {ConfigField_TimeRate_05, "rate05"},
        {ConfigField_TimeRate_075, "rate075"},
        {ConfigField_TimeRate_1, "rate1"},
        {ConfigField_TimeRate_3, "rate3"},
        {ConfigField_TimeRate_7, "rate7"},
        {ConfigField_VolumeValue_SFX, "sfx"},
        {ConfigField_VolumeValue_Music, "music"},
};

//TODO: need a better way to access arguments addresses. mb you should consider using string concatenation
//and some combination logic, to build all requerd addresses from only one argument, that is been searched
static std::unordered_map<ConfigField, const char*> argumentsAddressMap
{
        {ConfigField_WindowResolution_X, "/settings/window_resolution"},
        {ConfigField_WindowResolution_Y, "/settings/window_resolution"},
        {ConfigField_TimeRate_001, "/settings/time_rates"},
        {ConfigField_TimeRate_05, "/settings/time_rates"},
        {ConfigField_TimeRate_075, "/settings/time_rates"},
        {ConfigField_TimeRate_1, "/settings/time_rates"},
        {ConfigField_TimeRate_3, "/settings/time_rates"},
        {ConfigField_TimeRate_7, "/settings/time_rates"},
        {ConfigField_VolumeValue_SFX, "/settings/volume"},
        {ConfigField_VolumeValue_Music, "/settings/volume"},
};

ConfigManager::ConfigManager() : m_filePath("config.xml") {}

ConfigManager* ConfigManager::instance()
{
	static ConfigManager* m_ptrConfigManager = new ConfigManager();
	return m_ptrConfigManager;
}


//TODO: gathering float numbers is not really working. tryed with float as return type etc. still doesn't
//really work. need to rethink the way i get values from xml
int ConfigManager::getConfig(ConfigField argToGet)
{
    int returnValue;
    pugi::xml_document doc;

    if (doc.load_file(m_filePath))
    {
        returnValue = doc.select_node(argumentsAddressMap.find(argToGet)->second).node()
                    .attribute(argumentsMapping.find(argToGet)->second).as_int();
    }
    else
    {
        std::cout << "Error loading XML file." << std::endl;
    }
    return returnValue;
}

void ConfigManager::setConfig(ConfigField argToSet, int value)
{
    pugi::xml_document doc;
    if (doc.load_file(m_filePath))
    {
        doc.select_node(argumentsAddressMap.find(argToSet)->second).node().attribute(argumentsMapping
        .find(argToSet)->second).set_value(value);
        if (doc.save_file("config.xml"))
        {
            std::cout << "XML file saved successfully." << std::endl;
        }
        else
        {
            std::cout << "Error saving XML file." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error loading XML file." << std::endl;
    }
}
