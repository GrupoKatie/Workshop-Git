/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File3b;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 *
 * @author anive
 */
public class Link {
    private static Connection link;
    private static String DataLink = "jdbc:postgresql://localhost:5433/AutoMobile";
    private static String LogName = "postgres";
    private static String PassWord = "paulojO0";
    
    private Link(){}
    
    
    
    public static Connection Connect(){
        
        try{
            return DriverManager.getConnection(DataLink, LogName, PassWord);
            //System.out.println("Conectado!");
            
        }catch (SQLException e){
            //System.out.println("Erro de conexão com o BD: "+e.getMessage());
            throw new RuntimeException(e);
        }
    }
}
