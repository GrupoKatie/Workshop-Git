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
    
   public void getAlter(String comboName, JTextField IdF, JTextField ModelF, JTextField BrandF, JTextField YearF){
       
        try{
            String sql = "SELECT * FROM vehicles WHERE model = ?";
                PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                pstmt.setString(1, comboName);
                ResultSet rs = pstmt.executeQuery();
                
                if(rs != null){
                    while(rs.next()){
                        IdF.setText(rs.getString("id"));
                        ModelF.setText(rs.getString("model"));
                        BrandF.setText(rs.getString("brand"));
                        YearF.setText(rs.getString("year"));
                    }
                }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
   }
   
   public void AlterSave(JTextField IdF, JTextField ModelF, JTextField BrandF, JTextField YearF, JComboBox Data){
       if(IdF.getText().isEmpty() || ModelF.getText().isEmpty() || BrandF.getText().isEmpty() || YearF.getText().isEmpty()){
           JOptionPane.showMessageDialog(null, "Favor não deixar nenhum campo vazio para realizar as alterações.");
       }else {
           Automobile a = new Automobile(ModelF.getText(), BrandF.getText(), YearF.getText());
           a.setId(Integer.parseInt(IdF.getText()));
           AlterData(a);
           
           Data.removeAllItems();
           comboLogModel(Data);
           
           IdF.setText("");
           ModelF.setText("");
           BrandF.setText("");
           YearF.setText("");
           JOptionPane.showMessageDialog(null, "Alterado com sucesso!");
       }
   }
   // 
   public void Delete(JTextField IdF, JTextField ModelF, JTextField BrandF, JTextField YearF, JComboBox Data){
       if(IdF.getText().isEmpty() || ModelF.getText().isEmpty() || BrandF.getText().isEmpty() || YearF.getText().isEmpty()){
           JOptionPane.showMessageDialog(null, "Favor Escolha um veículo para ser Excluído.");
       }else {
           Automobile a = new Automobile(ModelF.getText(), BrandF.getText(), YearF.getText());
           a.setId(Integer.parseInt(IdF.getText()));
           RemoveData(a);
           
           Data.removeAllItems();
           comboLogModel(Data);
           
           IdF.setText("");
           ModelF.setText("");
           BrandF.setText("");
           YearF.setText("");
           
           JOptionPane.showMessageDialog(null, "Veículo "+a.getModel()+" deletado com Sucesso.");
       }
   }
   
   public void AlterData(Automobile auto){
       try{
            String sql = "Update vehicles set model = ?, brand = ?, year = ? where id = ?";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                    
                    pstmt.setLong(4, auto.getId());
                    pstmt.setString(1, auto.getModel());
                    pstmt.setString(2, auto.getBrand());
                    pstmt.setString(3, auto.getYear());
                    
                    pstmt.execute();
                    pstmt.close();
                    
                    
                    
        }catch(Exception e){
            System.out.println("Ocorreu um erro: " +e.getMessage());
            throw new RuntimeException(e);
    }
   }
   
   public void RemoveData(Automobile auto){
       try{
            String sql = "delete from vehicles where id = ?";
            PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                    
                    pstmt.setLong(1, auto.getId());
                    
                    pstmt.execute();
                    pstmt.close();
                    
                    
                    
        }catch(Exception e){
            System.out.println("Ocorreu um erro: " +e.getMessage());
            throw new RuntimeException(e);
    }
   }
   
   
   
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
                clearTable(table);
                if(rs != null){
	int row = 0;
	int col = 0;
                    while(rs.next()){
                        table.setValueAt(rs.getString("id"), row, col);
                        //System.out.println(rs.getString("id"));
                        col++;
                        
                        table.setValueAt(rs.getString("model"), row, col);
                        //System.out.println(rs.getString("model"));
                        col++;
                        
                        table.setValueAt(rs.getString("brand"), row, col);
                        //System.out.println(rs.getString("brand"));
                        col++;
                        
                        table.setValueAt(rs.getString("year"), row, col);
                        //System.out.println(rs.getString("year"));
                        row++;
                        col = 0;
                    }
                }
            
            pstmt.close();
        }catch (Exception e){
            System.out.println("Erro ao efetuar consulta no BD: "+e.getMessage());
        }
    }
    
     public void showDataBrand(String comboBrand, JTable table){
        try{
            String sql = "SELECT * FROM vehicles WHERE brand = ?";
                PreparedStatement pstmt = (PreparedStatement) this.link.prepareStatement(sql);
                pstmt.setString(1, comboBrand);
                ResultSet rs = pstmt.executeQuery();
                clearTable(table);
                if(rs != null){
	int row = 0;
	int col = 0;
                    while(rs.next()){
                        table.setValueAt(rs.getString("id"), row, col);
                         //System.out.println(rs.getString("id"));
                        col++;
                        
                        table.setValueAt(rs.getString("model"), row, col);
                        //System.out.println(rs.getString("model"));
                        col++;
                        
                        table.setValueAt(rs.getString("brand"), row, col);
                        //System.out.println(rs.getString("brand"));
                        col++;
                        
                        table.setValueAt(rs.getString("year"), row, col);
                        //System.out.println(rs.getString("year"));
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
                clearTable(table);
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
    
    public void clearTable(JTable table){
        var rows = table.getRowCount();
        var cols = table.getColumnCount();
        int col = 0;
        int row = 0;
        
        while(row < rows){
            col = 0;
            while(col < cols){
                table.setValueAt("", row, col);
                col++;
            }
            row++;
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
