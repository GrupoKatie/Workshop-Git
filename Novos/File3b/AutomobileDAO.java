/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package File3b;

import java.sql.*;
import java.util.LinkedList;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;

public class AutomobileDAO {

    private Connection link;
    
    public AutomobileDAO(){
        this.link = Link.Connect();
    }
    
    public void DataInsert(String m, String b, String y){
        try{
            String sql = "INSERT INTO vehicles (model, brand, year) values (?, ?, ?)";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                    pstmt.setString(1, m);
                    pstmt.setString(2, b);
                    pstmt.setString(3, y);
                    
                    pstmt.execute();
                    pstmt.close();
                    JOptionPane.showMessageDialog(null, "Adicionado com sucesso!");
                    
                    
        }catch(Exception e){
            throw new RuntimeException(e);
    }
    }
    
    public LinkedList<Automobile> list() {
		String sql = "select * from vehicles ORDER BY id";
		
		try {
			LinkedList<Automobile> Vehicles = new LinkedList<Automobile>();
			PreparedStatement stmt = this.link.prepareStatement(sql);
			ResultSet rs = stmt.executeQuery();

			while (rs.next()) {
				// Criando o objeto Automobile
				Automobile AM = new Automobile(rs.getString("model"), rs.getString("brand"), rs.getString("year"));
				AM.setId(rs.getInt("id"));				

				// Adicionando o objeto à lista
				Vehicles.add(AM);
			}
			rs.close();
			stmt.close();
			return Vehicles;
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
    
    /*
    public LinkedList<String> listModel(){
        String sql = "SELECT DISTINCT model FROM automobile ORDER BY model";
    
        try{
            LinkedList<String> models = new LinkedList<String>();
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                while (rs.next()){
                    models.add(rs.getString("model"));
                }
            }
            rs.close();
            pstmt.close();
            return models;
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
        
    }
    
     public LinkedList<String> listBrand(){
        String sql = "SELECT DISTINCT brand FROM automobile ORDER BY brand";
    
        try{
            LinkedList<String> brands = new LinkedList<String>();
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                while (rs.next()){
                    brands.add(rs.getString("brand"));
                }
            }
            rs.close();
            pstmt.close();
            return brands;
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
        
    }
     
      public LinkedList<String> listYear(){
        String sql = "SELECT DISTINCT year FROM automobile ORDER BY year";
    
        try{
            LinkedList<String> years = new LinkedList<String>();
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                while (rs.next()){
                    years.add(rs.getString("year"));
                }
            }
            rs.close();
            pstmt.close();
            return years;
        }catch (SQLException e){
            throw new RuntimeException(e);
        }
        
    }
    
    public void fillCombo(JComboBox MB, JComboBox BB, JComboBox YB){
        LinkedList<String> models = listModel();
        MB.addItem("Selecione um modelo:");
        for(String n : models){
            MB.addItem(n);
        }
    
        LinkedList<String> brands = listBrand();
        BB.addItem("Selecione uma marca:");
        for(String n : brands){
            BB.addItem(n);
        }
        
        LinkedList<String> years = listYear();
        YB.addItem("Selecione uma marca:");
        for(String n : years){
            YB.addItem(n);
        }
        
    }
      */
    public void comboLogModel(JComboBox CB){
        try{
            String sql = "SELECT DISTINCT model FROM vehicles ORDER BY model";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                int row = 0;
                while (rs.next()){
                    CB.insertItemAt(rs.getString("model"), row);
                    row++;
                }
            }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void comboLogYear(JComboBox CB){
        try{
            String sql = "SELECT DISTINCT year FROM vehicles ORDER BY year";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                int row = 0;
                while (rs.next()){
                    CB.insertItemAt(rs.getString("year"), row);
                    row++;
                }
            }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void comboLogBrand(JComboBox CB){
        try{
            String sql = "SELECT DISTINCT brand FROM vehicles ORDER BY brand";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                int row = 0;
                while (rs.next()){
                    CB.insertItemAt(rs.getString("brand"), row);
                    row++;
                }
            }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void showDataModel(String comboName, JTable table){
        try{
            String sql = "SELECT * FROM vehicles WHERE model = ?";
                PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                pstmt.setString(1, comboName);
                ResultSet rs = pstmt.executeQuery();
                if(rs != null){
	int row = 0;
	int col = 0;
                    while(rs.next()){
                        table.setValueAt(rs.getString("id"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("model"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("brand"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getInt("year"), row, col);
                        row++;
                        col = 0;
                        
                    }
	
	
                }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void showDataBrand(String comboName, JTable table){
        try{
            String sql = "SELECT * FROM vehicles WHERE brand = ?";
                PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                pstmt.setString(1, comboName);
                ResultSet rs = pstmt.executeQuery();
                DefaultTableModel tableM = (DefaultTableModel) table.getModel();
                    while(table.getRowCount() > 0){
                        tableM.removeRow(0);
                    }
                if(rs != null){
	int row = 0;
	int col = 0;
                    while(rs.next()){
                        
                          
                        
                        table.setValueAt(rs.getString("id"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("model"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("brand"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getInt("year"), row, col);
                        row++;
                        col = 0;
                        
                    }
	
	
                }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void showDataYear(String comboYear, JTable table){
        try{
            String sql = "SELECT * FROM vehicles WHERE year = ?";
                PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                pstmt.setString(1, comboYear);
                ResultSet rs = pstmt.executeQuery();
                if(rs != null){
	int row = 0;
	int col = 0;
                    while(rs.next()){
                        table.setValueAt(rs.getString("id"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("model"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("brand"), row, col);
                        col++;
                        
                        table.setValueAt(rs.getString("year"), row, col);
                        row++;
                        col = 0;
                        
                    }
	
	
                }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    public void showAll2(JTable table){
	LinkedList<Automobile> list = list();
                    DefaultTableModel tableM = (DefaultTableModel) table.getModel();
                    while(table.getRowCount() > 0){
                        tableM.removeRow(0);
                    }
	for(Automobile automobile  :  list){
		tableM.addRow(new String[] {automobile.getId()+"", automobile.getModel(), automobile.getBrand(), automobile.getYear()});
	}
}
    
    public void showAll(JTable DataTable){
        var rows = DataTable.getRowCount();
        var cols = DataTable.getColumnCount();
        int col = 0;
        int row = 0;
        try{
            String sql = "SELECT * FROM vehicles ORDER BY id";
            PreparedStatement pstmt = (PreparedStatement) link.prepareStatement(sql);
            ResultSet rs = pstmt.executeQuery();
            if( rs != null){
                while (rs.next()){
                    
                        DataTable.setValueAt(rs.getString("id"), row, col);
                        col++;
                        
                        DataTable.setValueAt(rs.getString("model"), row, col);
                        col++;
                        
                        DataTable.setValueAt(rs.getString("brand"), row, col);
                        col++;
                        
                        DataTable.setValueAt(rs.getString("year"), row, col);
                        row++;
                        col = 0;
                    
                    
                }
            }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
    
}
