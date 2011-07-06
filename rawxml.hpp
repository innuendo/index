class RawXML {
    std::string xml_text;
    
public:
    RawXML(std::string xml) : xml_text(xml) {}
    virtual std::string get_xml() {
        return xml_text;
    }
    RawXML(RawXML& rx) : xml_text(rx.get_xml()) {};
    RawXML() {}
};