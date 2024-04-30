#ifndef LIBRARY_H
#define LIBRARY_H
#include "../model/Library.cpp"
#endif


class Query
{
private:
    

public:
    
    Query()
    {
        
    }

    static std::string clean(std::string& param)
    {
        std::regex pattern("[^a-zA-Z0-9\n]");

        // Rimuovi i caratteri non alfanumerici
        std::string result = std::regex_replace(param, pattern, "");

        // Rimuovi il carattere di nuova linea (\n) finale se presente
        if (!result.empty() && result.back() == '\n')
        {
            result.pop_back();
        }

        return result;
    }

    std::string checkUscita(std::string tag_content)
    {
        return "SELECT * FROM Personale p, Timbrature t WHERE p.tag_content = '" + tag_content + "' AND p.id = t.fk_persona AND t.uscita IS NULL";
    }
    std::string createNewTag(std::string persona_id, std::string mac_tag)
    {
        return "INSERT INTO  Tags(id ,fk_persona,mac_tag ) VALUES (NULL, '" + persona_id + "', '" + mac_tag + "')";
    }

    std::string timbraEntrata(std::string persona_id)
    {
        return "INSERT INTO `Timbrature` (`id`, `fk_persona`,  `entrata`, `uscita`) VALUES (NULL, '" + persona_id + "', CURRENT_TIMESTAMP, NULL)";
    }

    std::string timbraUscita(std::string persona_id)
    {
        return "UPDATE Timbrature SET uscita = CURRENT_TIMESTAMP WHERE fk_persona = '" + persona_id + "' AND uscita IS NULL";
    }

    std::string getAllPersonale()
    {
        return "SELECT * FROM Personale";
    }
    std::string getAllTags()
    {
        return "SELECT * FROM Tags";
    }
    std::string getAllPersonaMacTags(std::string tag_content)
    {
        return "SELECT p.mac_tag  FROM Tags t,Persona p  WHERE tag_content = " + tag_content + " AND p.id = t.fk_persona";
    }

    std::string getPersonaID(std::string tag_content)
    {
        return "SELECT p.id  FROM Personale p  WHERE tag_content = '" + tag_content + "';";
    }

    std::string checkTag(std::string mac_tag, std::string tag_content){
        return "SELECT p.id FROM Tags t, Personale p WHERE p.tag_content = '" + tag_content + "' AND p.id = t.fk_persona AND t.mac_tag = '" + mac_tag + "';";
    }

    std::string getPersonaId(std::string tag_content)
    {
        return "SELECT id FROM Personale WHERE tag_content = " + tag_content;
    }

    std::string getTagContent(std::string persona_id)
    {
        return "SELECT tag_content FROM Personale WHERE id = " + persona_id;
    }

    std::string checkTagToWrite()
    {
        return "SELECT * FROM ToWrite LIMIT 1;";
    }

    std::string deleteTagToWrite(std::string id)
    {
        return "DELETE FROM ToWrite WHERE id = " + id + ";";
    }

    std::string OreLavorateMesePrecedente(){
        return "SELECT nome, ore_lavorate FROM `OreLavorateMesePrecedente`;";
    }
    std::string OreLavorateMesePrecedente(std::string id ){
        return "SELECT nome, ore_lavorate FROM `OreLavorateMesePrecedente`  WHERE id = " + id + ";";
    }
    std::string OreLavorateMesePrecedente_detaild(){
        return "SELECT nome,entrata,uscita FROM `OreLavorate30ggDettagli`;";
    }
    std::string OreLavorateMesePrecedente_detaild(std::string id ){
        return "SELECT nome,entrata,uscita FROM `OreLavorate30ggDettagli`  WHERE id = " + id + ";";
    }
    
};
#ifdef TEST_QUERY

void BuzzerQuery5()
{
    
}

int main()
{
    BuzzerQuery5();
}

#endif