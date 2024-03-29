USE [master]
GO
/****** Object:  Database [LibrarySystem]    Script Date: 2021/1/23 0:20:19 ******/
CREATE DATABASE [LibrarySystem]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'LibrarySystem_mdf', FILENAME = N'D:\SQL Sever\MSSQL15.MSSQLSERVER\MSSQL\DATA\LibrarySystem.mdf' , SIZE = 10240KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10240KB ),
( NAME = N'LibrarySystem_ndf', FILENAME = N'D:\SQL Sever\MSSQL15.MSSQLSERVER\MSSQL\DATA\LibrarySystem.ndf' , SIZE = 10240KB , MAXSIZE = UNLIMITED, FILEGROWTH = 10%)
 LOG ON 
( NAME = N'LibrarySystem_ldf', FILENAME = N'D:\SQL Sever\MSSQL15.MSSQLSERVER\MSSQL\DATA\LibrarySystem_log.ldf' , SIZE = 10240KB , MAXSIZE = 65536KB , FILEGROWTH = 10%)
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [LibrarySystem] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [LibrarySystem].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [LibrarySystem] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [LibrarySystem] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [LibrarySystem] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [LibrarySystem] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [LibrarySystem] SET ARITHABORT OFF 
GO
ALTER DATABASE [LibrarySystem] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [LibrarySystem] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [LibrarySystem] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [LibrarySystem] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [LibrarySystem] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [LibrarySystem] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [LibrarySystem] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [LibrarySystem] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [LibrarySystem] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [LibrarySystem] SET  ENABLE_BROKER 
GO
ALTER DATABASE [LibrarySystem] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [LibrarySystem] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [LibrarySystem] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [LibrarySystem] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [LibrarySystem] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [LibrarySystem] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [LibrarySystem] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [LibrarySystem] SET RECOVERY FULL 
GO
ALTER DATABASE [LibrarySystem] SET  MULTI_USER 
GO
ALTER DATABASE [LibrarySystem] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [LibrarySystem] SET DB_CHAINING OFF 
GO
ALTER DATABASE [LibrarySystem] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [LibrarySystem] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [LibrarySystem] SET DELAYED_DURABILITY = DISABLED 
GO
ALTER DATABASE [LibrarySystem] SET ACCELERATED_DATABASE_RECOVERY = OFF  
GO
EXEC sys.sp_db_vardecimal_storage_format N'LibrarySystem', N'ON'
GO
ALTER DATABASE [LibrarySystem] SET QUERY_STORE = OFF
GO
USE [LibrarySystem]
GO
/****** Object:  Table [dbo].[Administrator]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Administrator](
	[adminID] [varchar](50) NOT NULL,
	[adminSex] [varchar](50) NOT NULL,
	[adminAge] [varchar](50) NOT NULL,
	[adminName] [varchar](50) NOT NULL,
 CONSTRAINT [PK_Administrator] PRIMARY KEY CLUSTERED 
(
	[adminID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[adminPassword]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[adminPassword](
	[adminID] [varchar](50) NOT NULL,
	[AdminPassword] [varchar](50) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[BOOK]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BOOK](
	[ISBN] [varchar](20) NOT NULL,
	[BookName] [varchar](50) NOT NULL,
	[Author] [varchar](50) NOT NULL,
	[Isborrowed] [tinyint] NOT NULL,
	[Permission] [varchar](50) NOT NULL,
	[Addr] [varchar](50) NOT NULL,
	[Press] [varchar](50) NOT NULL,
	[Introduction] [text] NULL,
 CONSTRAINT [PK_BOOK] PRIMARY KEY CLUSTERED 
(
	[ISBN] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
/****** Object:  Table [dbo].[StuBook]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StuBook](
	[StuID] [varchar](20) NOT NULL,
	[BorrowedBookNum] [tinyint] NOT NULL,
	[BorrowedBookName] [varchar](50) NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Student]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Student](
	[StuID] [varchar](50) NOT NULL,
	[stuName] [varchar](50) NOT NULL,
	[stuSex] [varchar](50) NOT NULL,
	[Department] [varchar](50) NOT NULL,
	[SpecialityAndClass] [varchar](50) NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[StuFeedback_score]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[StuFeedback_score](
	[StuID] [varchar](10) NOT NULL,
	[Feedback_score] [tinyint] NOT NULL,
	[Violations] [tinyint] NOT NULL,
	[Arrearage] [int] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[stuPassword]    Script Date: 2021/1/23 0:20:19 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[stuPassword](
	[StuID] [varchar](50) NOT NULL,
	[StuPassword] [varchar](10) NOT NULL,
 CONSTRAINT [PK_StuPassword] PRIMARY KEY CLUSTERED 
(
	[StuID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
ALTER TABLE [dbo].[adminPassword] ADD  CONSTRAINT [DF__adminPass__admin__4222D4EF]  DEFAULT ('666666') FOR [AdminPassword]
GO
ALTER TABLE [dbo].[BOOK] ADD  DEFAULT ((1)) FOR [Isborrowed]
GO
ALTER TABLE [dbo].[BOOK] ADD  DEFAULT ('无') FOR [Introduction]
GO
ALTER TABLE [dbo].[StuBook] ADD  DEFAULT ((0)) FOR [BorrowedBookNum]
GO
ALTER TABLE [dbo].[StuFeedback_score] ADD  DEFAULT ((100)) FOR [Feedback_score]
GO
ALTER TABLE [dbo].[StuFeedback_score] ADD  DEFAULT ((0)) FOR [Violations]
GO
ALTER TABLE [dbo].[StuFeedback_score] ADD  DEFAULT ((0)) FOR [Arrearage]
GO
ALTER TABLE [dbo].[stuPassword] ADD  DEFAULT ('666666') FOR [StuPassword]
GO
ALTER TABLE [dbo].[Administrator]  WITH CHECK ADD  CONSTRAINT [CK_adminSex] CHECK  (([adminSex]='男' OR [adminSex]='女'))
GO
ALTER TABLE [dbo].[Administrator] CHECK CONSTRAINT [CK_adminSex]
GO
ALTER TABLE [dbo].[BOOK]  WITH CHECK ADD  CONSTRAINT [CK_Isborrowed] CHECK  (([Isborrowed]=(1) OR [Isborrowed]=(0)))
GO
ALTER TABLE [dbo].[BOOK] CHECK CONSTRAINT [CK_Isborrowed]
GO
ALTER TABLE [dbo].[BOOK]  WITH CHECK ADD  CONSTRAINT [CK_Permission] CHECK  (([Permission]='可供出借' OR [Permission]='仅供借阅'))
GO
ALTER TABLE [dbo].[BOOK] CHECK CONSTRAINT [CK_Permission]
GO
ALTER TABLE [dbo].[Student]  WITH CHECK ADD  CONSTRAINT [CK_stuSex] CHECK  (([stuSex]='男' OR [stuSex]='女'))
GO
ALTER TABLE [dbo].[Student] CHECK CONSTRAINT [CK_stuSex]
GO
USE [master]
GO
ALTER DATABASE [LibrarySystem] SET  READ_WRITE 
GO
